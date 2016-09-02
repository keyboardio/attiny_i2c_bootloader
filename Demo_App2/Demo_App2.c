#include <inavr.h>
#include <ioavr.h>

void main( void )
{
    
#if defined(__ATTINY25__)   | defined(__ATTINY25V__) | \
    defined(__ATTINY45__)   | defined(__ATTINY45V__) | \
    defined(__ATTINY85__)   | defined(__ATTINY85V__) | \
    defined(__ATTINY2313__) | defined(__ATTINY2313A__) | \
    defined(__ATTINY4313__) | defined(__ATTINY4313A__) | \
    defined(__ATTINY261__)  | defined(__ATTINY261A__) | \
    defined(__ATTINY461__)  | defined(__ATTINY461A__) | \
    defined(__ATTINY861__)  | defined(__ATTINY861A__) | \
    defined(__ATTINY43U__)  | \
    defined(__ATTINY87__)   | \
    defined(__ATTINY167__)  | \
    defined(__ATTINY48__) | defined(__ATTINY88__) | \
    defined(__ATMEGA48A__) | defined(__ATMEGA48PA__) | \
    defined(__ATMEGA48__)
  
	DDRB |= (1 << PORTB3);  // LED1 Connected here
#endif
        
#if defined(__ATTINY24__)   | defined(__ATTINY24A__) | \
    defined(__ATTINY44__)   | defined(__ATTINY44A__) | \
    defined(__ATTINY84__)   | defined(__ATTINY84A__) 
     
        DDRB |= (1 << PORTB2);  // LED1 Connected here
#endif     
       
	for (;;) 
        {
		#if defined(__ATTINY25__)   | defined(__ATTINY25V__) | \
                    defined(__ATTINY45__)   | defined(__ATTINY45V__) | \
                    defined(__ATTINY85__)   | defined(__ATTINY85V__) | \
                    defined(__ATTINY2313__) | defined(__ATTINY2313A__) | \
                    defined(__ATTINY4313__) | defined(__ATTINY4313A__) | \
                    defined(__ATTINY261__)  | defined(__ATTINY261A__) | \
                    defined(__ATTINY461__)  | defined(__ATTINY461A__) | \
                    defined(__ATTINY861__)  | defined(__ATTINY861A__) | \
                    defined(__ATTINY43U__)  | \
                    defined(__ATTINY87__)   | \
                    defined(__ATTINY167__)  | \
                    defined(__ATTINY48__) | defined(__ATTINY88__) | \
                    defined(__ATMEGA48A__) | defined(__ATMEGA48PA__) | \
                    defined(__ATMEGA48__)
            
                     PORTB ^= (1 << PORTB3);
                     __delay_cycles( 1000000 );
                      PORTB ^= ~(1 << PORTB3);
                     __delay_cycles( 1000000 );
                   
               #endif
                
               #if  defined(__ATTINY24__)   | defined(__ATTINY24A__) | \
                    defined(__ATTINY44__)   | defined(__ATTINY44A__) | \
                    defined(__ATTINY84__)   | defined(__ATTINY84A__) 
                
                    PORTB ^= (1 <<  PORTB2);
                    __delay_cycles( 1000000 );
                    PORTB ^= ~(1 << PORTB2);
                    __delay_cycles( 1000000 );
               #endif
                
		
	}
}














