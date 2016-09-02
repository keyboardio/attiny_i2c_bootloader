
#ifdef __USI__

#include "USI_TWI_Slave.h"
#include "Common_Define.h"

/*****************************************************************************/
// USI_TWI write states.
#define USI_TWI_WRITE_ADDR_HI_BYTE              (0x00)
#define USI_TWI_WRITE_ADDR_LO_BYTE              (0x01)
#define USI_TWI_WRITE_DATA_BYTE                 (0x02)

// USI_TWI overflow states.
#define USI_TWI_OVERFLOW_STATE_NONE             (0x00)
#define USI_TWI_OVERFLOW_STATE_ACK_PR_RX        (0x01)
#define USI_TWI_OVERFLOW_STATE_DATA_RX          (0x02)
#define USI_TWI_OVERFLOW_STATE_ACK_PR_TX        (0x03)
#define USI_TWI_OVERFLOW_STATE_PR_ACK_TX        (0x04)
#define USI_TWI_OVERFLOW_STATE_DATA_TX          (0x05)

// USI_TWI state values.
static uint8_t USI_TWI_SLAVE_Write_State;
static uint8_t USI_TWI_SLAVE_Overflow_State;
static uint8_t Command_Flag;

// TWI flag values.
static uint8_t USI_TWI_SLAVE_Address_Update;

// Slave Each page address values.
static uint16_t USI_TWI_SLAVE_PAGE_Address;

/******************************************************************************/

/* Local variables   */
static uint8_t TWI_RxBuf[TWI_RX_BUFFER_SIZE];
static volatile uint8_t TWI_RxHead;
static volatile uint8_t TWI_RxTail;

static uint8_t TWI_TxBuf[TWI_TX_BUFFER_SIZE];
static volatile uint8_t TWI_TxHead;
static volatile uint8_t TWI_TxTail;

static unsigned char USI_TWI_SlaveAddress;

//********** USI_TWI functions **********//
void USI_TWI_SLAVE_Init( uint8_t TWI_OwnAddress )
{
  
  USI_TWI_SlaveAddress = TWI_OwnAddress;
  
  DDR_USI  &= ~(1<<PORT_USI_SDA);      // Set SDA as input
  PORT_USI &=  ~(1<<PORT_USI_SDA);    // Set SDA high
  
  DDR_USI  |=  (1<<PORT_USI_SCL);      // Set SCL as output
  PORT_USI |=  (1<<PORT_USI_SCL);      // Set SCL high
   
  
  USICR    =  (0<<USISIE)|(0<<USIOIE)|                         // Disable Start Condition Interrupt. Disable Overflow Interrupt.
               (1<<USIWM1)|(0<<USIWM0)|                        // Set USI in Two-wire mode. No USI Counter overflow prior
                                                               // to first Start Condition (potentail failure)
               (1<<USICS1)|(0<<USICS0)|(0<<USICLK)|            // Shift Register Clock Source = External, positive edge
              (0<<USITC);
   
  // Clear the interrupt flags and reset the counter.   
  USISR = (1<<USISIF) | (1<<USIOIF) | (1<<USIPF) |        // Clear interrupt flags.
          (1<<USIDC) |(0x0<<USICNT0);                     // USI to sample 8 bits or 16 edge toggles.
  
   // USI TWI Start condition interrupt enable.
    USICR |= (1<<USISIE);
 }

 // the below function is added by 
/*****************************************************************************/ 
void USI_TWI_SLAVE_Abort()
{
  USICR    =  (0<<USISIE)|(0<<USIOIE)|                         // Disable Start Condition Interrupt. Disable Overflow Interrupt.
               (0<<USIWM1)|(0<<USIWM0)|                            // reset USI in Two-wire mode. No USI Counter overflow prior
                                                                 // to first Start Condition (potentail failure)
               (0<<USICS1)|(0<<USICS0)|(0<<USICLK)|                // Shift Register Clock Source = internal, positive edge
              (0<<USITC); 
  
  
  // Reset SCL and SDA lines of TWI Communication interface
   DDR_USI  &= ~(1<<PORT_USI_SDA);      
  PORT_USI &=  ~(1<<PORT_USI_SDA);    // Set SDA low
  
  DDR_USI  |=  ~(1<<PORT_USI_SCL);     
  PORT_USI |=  ~(1<<PORT_USI_SCL);      // Set SCL low
  
  // Clear the USI DATA register.
  USIDR = 0x00;
  
  // Clear the interrupt flags and reset the counter.   
  USISR = (1<<USISIF) | (1<<USIOIF) | (1<<USIPF) |        // Clear interrupt flags.
          (1<<USIDC) |(0x0<<USICNT0);                     // USI to sample 8 bits or 16 edge toggles.
  
}
 

void USI_TWI_SLAVE_ReadAndProcessPacket ()
{
   
   // Check for USI TWI start condition.
   if (USISR & (1<<USISIF))
   {
      // Process the USI TWI start condition.
      USI_TWI_SLAVE_Process_Start_Condition();
   }
  
   // Check for USI_TWI_SLAVE overflow condition.
   if (USISR & (1<<USIOIF))
   {
      // Handle the TWI overflow condition.
      USI_TWI_SLAVE_Process_Overflow_Condition();
      
     /*  as this part is already taken care...
      // Should we update the twi address?
      if (USI_TWI_SLAVE_Address_Update)
      {
          // Mark the bootloader as active.
          bootloader_active = 1;
          
          // Check for the special address to exit the bootloader.
          if (USI_TWI_SLAVE_PAGE_Address != 0xffff)
          {
            // Set the twi address.  This will load the corresponding page from
            // flash into the programming buffer for reading and writing.
            // prog_buffer_set_address(USI_TWI_SLAVE_PAGE_Address);
          }
          
          // Reset the flag.
          USI_TWI_SLAVE_Address_Update = 0;
      }
      
      .....Till here.........*/
      
   }
   
   // Check for TWI stop condition.
   if (USISR & (1<<USIPF))
   {
       // Clear the stop condition flag.
        USISR = (1<<USIPF);
        // Check for the special address to exit the bootloader.
        if (USI_TWI_SLAVE_PAGE_Address == 0xffff)
        {
          // Set the flag to have the bootloader eixt.
          bootloader_exit = 1;
        }
        else
        {
          // Update the programming buffer if needed.
          // kk prog_buffer_update();
        }
   }
     
}


/******************************************************************************/
//Description: 
// Process the USI TWI start condition.  This is called when the TWI master initiates
// communication with a USI TWI slave by asserting the TWI start condition.
/******************************************************************************/
void USI_TWI_SLAVE_Process_Start_Condition(void)
{    
    // Wait until the "Start Condition" is complete when SCL goes low. If we fail to wait
    // for SCL to go low we may miscount the number of clocks pulses for the data because
    // the transition of SCL could be mistaken as one of the data clock pulses.
    while ((PIN_USI & (1<<PORT_USI_SCL)));
    // Reset the overflow state.
    USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_NONE;
    // Clear the interrupt flags and reset the counter.
    USISR = (1<<USISIF) | (1<<USIOIF) | (1<<USIPF) |    // Clear interrupt flags.
            (0x00<<USICNT0);                            // USI to sample 8 bits or 16 edge toggles.
    
    // Update the interrupt enable, wire mode and clock settings.
    USICR = (1<<USISIE) | (1<<USIOIE) |                 // Enable Overflow and Start Condition Interrupt.
            (1<<USIWM1) | (1<<USIWM0) |                 // Maintain USI in two-wire mode with clock stretching.
            (1<<USICS1) | (0<<USICS0) | (0<<USICLK) |   // Shift Register Clock Source = External, positive edge
            (0<<USITC);                                 // No toggle of clock pin.
}

/******************************************************************************/


 //Buffer the entire page
  static uint8_t *bufferPtr = pageBuffer;
static uint8_t Value;


/*******************************************************************************
Description: 
Processes the USI_TWI_SLAVE overflow condition.  
This is called when the USI TWI 4-bit counterboverflows indicating the 
TWI master has clocked in/out a databyte or a singleback/nack byte following a 
databyte transfer.

*******************************************************************************/
void USI_TWI_SLAVE_Process_Overflow_Condition(void)
{    
    // Buffer the USI data.
    uint8_t Usi_Data = USIDR;
  
 
  
  // Handle the interrupt based on the overflow state.
  switch (USI_TWI_SLAVE_Overflow_State)
  {
    /***********************************************************************/
    // Handle the first byte transmitted from master -- the slave address.
    case USI_TWI_SLAVE_OVERFLOW_STATE_NONE:
      
      // Are we receiving our address?
      if ((Usi_Data >> 1) == USI_TWI_SlaveAddress)
      {
        // Yes. Are we to send or receive data?
        if((Usi_Data & 0x01) == 0x01)
        {
            //USI TWI Slave has to transmit the data byte
            USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_ACK_PR_TX;
        }
        else
        {
            //USI TWI Slave has to Receive the data byte
            USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_ACK_PR_RX;
        }
       
        
        // Reset the write state.
       //.. added the below statement at Command_flag=1
        //USI_TWI_SLAVE_Write_State = USI_TWI_SLAVE_WRITE_ADDR_HI_BYTE;
        
        // Set SDA for output.
        PORT_USI |= (1<<PORT_USI_SDA);
        DDR_USI |= (1<<PORT_USI_SDA);
        
        // Load data for ACK.
        USIDR = 0;
        
        // Reload counter for ACK -- two clock transitions.
        USISR = 0x0E;
        
      }
      else
      {
        // No. Reset USI to detect start condition.  Update the interrupt enable, 
        // wire mode and clock settings.  Note: At this time the wire mode must
        // not be set to hold the SCL line low when the counter overflows.  
        // Otherwise, this TWI slave will interfere with other TWI slaves.
        USICR = (1<<USISIE) | (0<<USIOIE) |                 // Enable Start Condition Interrupt. Disable overflow.
          (1<<USIWM1) | (0<<USIWM0) |                 // Maintain USI in two-wire mode without clock stretching.
            (1<<USICS1) | (0<<USICS0) | (0<<USICLK) |   // Shift Register Clock Source = External, positive edge
              (0<<USITC);                                 // No toggle of clock pin.
      }
      
      break;
       /***********************************************************************/   
      // Ack sent to master so prepare to receive more data.
  case USI_TWI_SLAVE_OVERFLOW_STATE_ACK_PR_RX:
    
      if(Command_Flag == 0)
      {
         // Update our state.
         USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_CMD_RX;
      }
      else if(Command_Flag == 1)
      {
         // Update our state.
         USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_DATA_RX;
         
           // Reset the write state.
           USI_TWI_SLAVE_Write_State = USI_TWI_SLAVE_WRITE_ADDR_HI_BYTE;
      }
      else if(Command_Flag == 2)
      {
        // Update our state.
         USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX_AVERSION;
      }
       else if(Command_Flag == 3)
      {
        // Update our state.
         USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX_BVERSION;
      }
       else if(Command_Flag == 4)
      {
        // Update our state.
         USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX_GETERRCONDN;
      }
       
    
     // Set SDA for input
     DDR_USI &= ~(1<<PORT_USI_SDA);
     PORT_USI &= ~(1<<PORT_USI_SDA);
    
     break;
    /**************************************************************************/
    
    
  case USI_TWI_SLAVE_OVERFLOW_STATE_CMD_RX:
       
     // Update our state
     //USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_ACK_PR_TX;
    USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_NONE;
   
    // USI_TWI_SLAVE_Command_Received = Usi_Data;
      
      // Check the command recieved type.
      if(Usi_Data == TWI_CMD_PAGEUPDATE)
      {
          // set this flag to receive data
          Command_Flag =1; 
      }
      else if(Usi_Data == TWI_CMD_EXECUTEAPP)
      {
          // reset the controller ... 
        
          // set this flag to receive data
          Command_Flag =0; 
        
      }
      else if(Usi_Data == TWI_CMD_AVERSION)
      {
          // set this flag to receive data
          Command_Flag =2; 
        
      }
      else if(Usi_Data == TWI_CMD_BVERSION)
      {
          // set this flag to receive data
          Command_Flag =3; 
        
      }
      else if(Usi_Data == TWI_CMD_ERASEFLASH)
      {
          // erase the flash here itself ....... 
        
          // set this flag to receive data
          Command_Flag =0; 
        
      }
      else if(Usi_Data == TWI_CMD_GETERRCONDN)
      {
          // set this flag to receive data
          Command_Flag =4; 
        
      }
      else
      {
          // set this flag to receive data
          Command_Flag =0; 
        
          USI_TWI_SLAVE_Abort();
      }
    break;
    
    // Data received from master so prepare to send ACK.
  case USI_TWI_SLAVE_OVERFLOW_STATE_DATA_RX:
    
    // Update our state.
    USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_ACK_PR_RX;
    
    // Always make sure the Command_Flag is 1
    Command_Flag = 1;
    
    // Check the TWI write state to determine what type of byte we received.
    if (USI_TWI_SLAVE_Write_State == USI_TWI_SLAVE_WRITE_ADDR_HI_BYTE)
    {
      // Set the twi address high byte.
      USI_TWI_SLAVE_PAGE_Address = Usi_Data;
      
      // Set the next state.
      USI_TWI_SLAVE_Write_State = USI_TWI_SLAVE_WRITE_ADDR_LO_BYTE;
    }
    else if (USI_TWI_SLAVE_Write_State == USI_TWI_SLAVE_WRITE_ADDR_LO_BYTE)
    {
      // Set the address low byte.
      USI_TWI_SLAVE_PAGE_Address = (USI_TWI_SLAVE_PAGE_Address << 8) | Usi_Data;
      
      // Set the programming address.
      USI_TWI_SLAVE_Address_Update = 1;
      
      // Set the next state.
      USI_TWI_SLAVE_Write_State = USI_TWI_SLAVE_WRITE_DATA_BYTE;
    }
    else
    {
        // Write the data to the buffer.
        //USI_TWI_SLAVE_prog_buffer_set_byte(Usi_Data);
      
        *bufferPtr = Usi_Data;
  
        // Increment the byte address within the page.
        //++prog_byte_address;
      
         ++bufferPtr;
          ++Value;
        // Check the byte address for wrapping. //  check later 
         if (Value >(PAGE_SIZE - 1)) 
        {
            UpdatePage (USI_TWI_SLAVE_PAGE_Address);  
             Value = 0;
             bufferPtr =0;
             
        }
       
      }
     
    
    // Set SDA for output.
    PORT_USI |= (1<<PORT_USI_SDA);
    DDR_USI |= (1<<PORT_USI_SDA);
    
    // Load data for ACK.
    USIDR = 0;
    
    // Reload counter for ACK -- two clock transitions.
    USISR = 0x0E;
    
    break;
     /***********************************************************************/
    
  case USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX_AVERSION:
    
     // Update our state.
    USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_PR_ACK_TX;
    
    // Set SDA for input.
    DDR_USI &= ~(1<<PORT_USI_SDA);
    PORT_USI &= ~(1<<PORT_USI_SDA);
    
    // Reload counter for ACK -- two clock transitions.
    USISR = 0x0E;
    
    break;
    
    /***********************************************************************/
     case USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX_BVERSION:
    
    break;
   /***********************************************************************/ 
     case USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX_GETERRCONDN:
    
    break;
  /***********************************************************************/  
    // ACK received from master.  Reset USI state if NACK received.
  case USI_TWI_SLAVE_OVERFLOW_STATE_PR_ACK_TX:
    
    // Check the lowest bit for NACK?  If set, the master does not want more data.
    if (Usi_Data & 0x01)
    {
      // Update our state.
      USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_NONE;
      
      // Reset USI to detect start condition. Update the interrupt enable,
      // wire mode and clock settings. Note: At this time the wire mode must
      // not be set to hold the SCL line low when the counter overflows.
      // Otherwise, this TWI slave will interfere with other TWI slaves.
      USICR = (1<<USISIE) | (0<<USIOIE) |                 // Enable Start Condition Interrupt. Disable overflow.
        (1<<USIWM1) | (0<<USIWM0) |                 // Maintain USI in two-wire mode without clock stretching.
          (1<<USICS1) | (0<<USICS0) | (0<<USICLK) |   // Shift Register Clock Source = External, positive edge
            (0<<USITC);                                 // No toggle of clock pin.
      
      
      // Clear the overflow interrupt flag and release the hold on SCL.
      USISR |= (1<<USIOIF);
      
      return;
    }
    
    
    
     /***********************************************************************/   
    // Handle sending a byte of data.
  case USI_TWI_SLAVE_OVERFLOW_STATE_ACK_PR_TX:
    
    // Update our state.
   // USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX;
     USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX_AVERSION;
    
    // Set SDA for output.
    PORT_USI |= (1<<PORT_USI_SDA);
    DDR_USI |= (1<<PORT_USI_SDA);
    
    // Get the data to send.
    // USIDR = prog_buffer_get_byte();
    USIDR = 0X33;
    
    break;
   /***********************************************************************/
    
    // Data sent to to master so prepare to receive ack.
  case USI_TWI_SLAVE_OVERFLOW_STATE_DATA_TX:
    
    // Update our state.
    USI_TWI_SLAVE_Overflow_State = USI_TWI_SLAVE_OVERFLOW_STATE_PR_ACK_TX;
    
    // Set SDA for input.
    DDR_USI &= ~(1<<PORT_USI_SDA);
    PORT_USI &= ~(1<<PORT_USI_SDA);
    
    // Reload counter for ACK -- two clock transitions.
    USISR = 0x0E;
    
    break;
   /***********************************************************************/
  }
  // Clear the overflow interrupt flag and release the hold on SCL.
  USISR |= (1<<USIOIF);
}



/******************************************************************************/
/*
void prog_buffer_set_byte(uint8_t databyte)
// Set the byte at the current address.
{
  
  uint8_t *bufferPtr = pageBuffer;
  
  // Protect the bootloader by protecting the reset vector from being
  // overwritten. The reset vector is the first two byte of the first page.
  if ((prog_page_address != 0) || ((*bufferPtr != 0) && (*bufferPtr != 1)))
  {
    // Set the byte within the programming buffer.
    //prog_buffer[prog_byte_address] = databyte;
    *bufferPtr = databyte;
  }
  
  // Increment the byte address within the page.
  //++prog_byte_address;
   ++bufferPtr;
  
  // Check the byte address for wrapping.
  if (*bufferPtr >(PAGE_SIZE - 1)) 
      *bufferPtr = 0;
  
  // Set the programming update flag.  This indicates the programming
  // buffer should be written to Flash.
  prog_update_flag = 1;
}

*/


#endif

