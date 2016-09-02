
















 
 












 

#pragma system_include













 

#pragma system_include




 



















  
  








































 

























 
















 
 
 

 
 
 

 







 

#pragma language=save
#pragma language=extended

 
 
 





























































 

__ext_io union { unsigned char UDR3; struct { unsigned char UDR3_Bit0:1, UDR3_Bit1:1, UDR3_Bit2:1, UDR3_Bit3:1, UDR3_Bit4:1, UDR3_Bit5:1, UDR3_Bit6:1, UDR3_Bit7:1; }; } @ 0x136;
__ext_io union { unsigned short UBRR3; struct { unsigned char UBRR3_Bit0:1, UBRR3_Bit1:1, UBRR3_Bit2:1, UBRR3_Bit3:1, UBRR3_Bit4:1, UBRR3_Bit5:1, UBRR3_Bit6:1, UBRR3_Bit7:1; unsigned char UBRR3_Bit8:1, UBRR3_Bit9:1, UBRR3_Bit10:1, UBRR3_Bit11:1, UBRR3_Bit12:1, UBRR3_Bit13:1, UBRR3_Bit14:1, UBRR3_Bit15:1; }; struct { unsigned char UBRR3L; unsigned char UBRR3H; }; struct { unsigned char UBRR3L_Bit0:1, UBRR3L_Bit1:1, UBRR3L_Bit2:1, UBRR3L_Bit3:1, UBRR3L_Bit4:1, UBRR3L_Bit5:1, UBRR3L_Bit6:1, UBRR3L_Bit7:1; unsigned char UBRR3H_Bit0:1, UBRR3H_Bit1:1, UBRR3H_Bit2:1, UBRR3H_Bit3:1, UBRR3H_Bit4:1, UBRR3H_Bit5:1, UBRR3H_Bit6:1, UBRR3H_Bit7:1; }; } @ 0x134;
__ext_io union { unsigned char UCSR3C; struct { unsigned char UCSR3C_Bit0:1, UCSR3C_Bit1:1, UCSR3C_Bit2:1, UCSR3C_Bit3:1, UCSR3C_Bit4:1, UCSR3C_Bit5:1, UCSR3C_Bit6:1, UCSR3C_Bit7:1; }; struct { unsigned char UCSR3C_UCPOL3:1, UCSR3C_UCSZ30:1, UCSR3C_UCSZ31:1, UCSR3C_USBS3:1, UCSR3C_UPM30:1, UCSR3C_UPM31:1, UCSR3C_UMSEL30:1, UCSR3C_UMSEL31:1; }; struct{ unsigned char :5; unsigned char UCSR3C_UDORD3:1; unsigned char UCSR3C_UCPHA3:1; unsigned char :1;}; } @ 0x132;
__ext_io union { unsigned char UCSR3B; struct { unsigned char UCSR3B_Bit0:1, UCSR3B_Bit1:1, UCSR3B_Bit2:1, UCSR3B_Bit3:1, UCSR3B_Bit4:1, UCSR3B_Bit5:1, UCSR3B_Bit6:1, UCSR3B_Bit7:1; }; struct { unsigned char UCSR3B_TXB83:1, UCSR3B_RXB83:1, UCSR3B_UCSZ32:1, UCSR3B_TXEN3:1, UCSR3B_RXEN3:1, UCSR3B_UDRIE3:1, UCSR3B_TXCIE3:1, UCSR3B_RXCIE3:1; }; } @ 0x131;
__ext_io union { unsigned char UCSR3A; struct { unsigned char UCSR3A_Bit0:1, UCSR3A_Bit1:1, UCSR3A_Bit2:1, UCSR3A_Bit3:1, UCSR3A_Bit4:1, UCSR3A_Bit5:1, UCSR3A_Bit6:1, UCSR3A_Bit7:1; }; struct { unsigned char UCSR3A_MPCM3:1, UCSR3A_U2X3:1, UCSR3A_UPE3:1, UCSR3A_DOR3:1, UCSR3A_FE3:1, UCSR3A_UDRE3:1, UCSR3A_TXC3:1, UCSR3A_RXC3:1; }; } @ 0x130;
__ext_io union { unsigned short OCR5C; struct { unsigned char OCR5C_Bit0:1, OCR5C_Bit1:1, OCR5C_Bit2:1, OCR5C_Bit3:1, OCR5C_Bit4:1, OCR5C_Bit5:1, OCR5C_Bit6:1, OCR5C_Bit7:1; unsigned char OCR5C_Bit8:1, OCR5C_Bit9:1, OCR5C_Bit10:1, OCR5C_Bit11:1, OCR5C_Bit12:1, OCR5C_Bit13:1, OCR5C_Bit14:1, OCR5C_Bit15:1; }; struct { unsigned char OCR5CL; unsigned char OCR5CH; }; struct { unsigned char OCR5CL_Bit0:1, OCR5CL_Bit1:1, OCR5CL_Bit2:1, OCR5CL_Bit3:1, OCR5CL_Bit4:1, OCR5CL_Bit5:1, OCR5CL_Bit6:1, OCR5CL_Bit7:1; unsigned char OCR5CH_Bit0:1, OCR5CH_Bit1:1, OCR5CH_Bit2:1, OCR5CH_Bit3:1, OCR5CH_Bit4:1, OCR5CH_Bit5:1, OCR5CH_Bit6:1, OCR5CH_Bit7:1; }; } @ 0x12C;
__ext_io union { unsigned short OCR5B; struct { unsigned char OCR5B_Bit0:1, OCR5B_Bit1:1, OCR5B_Bit2:1, OCR5B_Bit3:1, OCR5B_Bit4:1, OCR5B_Bit5:1, OCR5B_Bit6:1, OCR5B_Bit7:1; unsigned char OCR5B_Bit8:1, OCR5B_Bit9:1, OCR5B_Bit10:1, OCR5B_Bit11:1, OCR5B_Bit12:1, OCR5B_Bit13:1, OCR5B_Bit14:1, OCR5B_Bit15:1; }; struct { unsigned char OCR5BL; unsigned char OCR5BH; }; struct { unsigned char OCR5BL_Bit0:1, OCR5BL_Bit1:1, OCR5BL_Bit2:1, OCR5BL_Bit3:1, OCR5BL_Bit4:1, OCR5BL_Bit5:1, OCR5BL_Bit6:1, OCR5BL_Bit7:1; unsigned char OCR5BH_Bit0:1, OCR5BH_Bit1:1, OCR5BH_Bit2:1, OCR5BH_Bit3:1, OCR5BH_Bit4:1, OCR5BH_Bit5:1, OCR5BH_Bit6:1, OCR5BH_Bit7:1; }; } @ 0x12A;
__ext_io union { unsigned short OCR5A; struct { unsigned char OCR5A_Bit0:1, OCR5A_Bit1:1, OCR5A_Bit2:1, OCR5A_Bit3:1, OCR5A_Bit4:1, OCR5A_Bit5:1, OCR5A_Bit6:1, OCR5A_Bit7:1; unsigned char OCR5A_Bit8:1, OCR5A_Bit9:1, OCR5A_Bit10:1, OCR5A_Bit11:1, OCR5A_Bit12:1, OCR5A_Bit13:1, OCR5A_Bit14:1, OCR5A_Bit15:1; }; struct { unsigned char OCR5AL; unsigned char OCR5AH; }; struct { unsigned char OCR5AL_Bit0:1, OCR5AL_Bit1:1, OCR5AL_Bit2:1, OCR5AL_Bit3:1, OCR5AL_Bit4:1, OCR5AL_Bit5:1, OCR5AL_Bit6:1, OCR5AL_Bit7:1; unsigned char OCR5AH_Bit0:1, OCR5AH_Bit1:1, OCR5AH_Bit2:1, OCR5AH_Bit3:1, OCR5AH_Bit4:1, OCR5AH_Bit5:1, OCR5AH_Bit6:1, OCR5AH_Bit7:1; }; } @ 0x128;
__ext_io union { unsigned short ICR5; struct { unsigned char ICR5_Bit0:1, ICR5_Bit1:1, ICR5_Bit2:1, ICR5_Bit3:1, ICR5_Bit4:1, ICR5_Bit5:1, ICR5_Bit6:1, ICR5_Bit7:1; unsigned char ICR5_Bit8:1, ICR5_Bit9:1, ICR5_Bit10:1, ICR5_Bit11:1, ICR5_Bit12:1, ICR5_Bit13:1, ICR5_Bit14:1, ICR5_Bit15:1; }; struct { unsigned char ICR5L; unsigned char ICR5H; }; struct { unsigned char ICR5L_Bit0:1, ICR5L_Bit1:1, ICR5L_Bit2:1, ICR5L_Bit3:1, ICR5L_Bit4:1, ICR5L_Bit5:1, ICR5L_Bit6:1, ICR5L_Bit7:1; unsigned char ICR5H_Bit0:1, ICR5H_Bit1:1, ICR5H_Bit2:1, ICR5H_Bit3:1, ICR5H_Bit4:1, ICR5H_Bit5:1, ICR5H_Bit6:1, ICR5H_Bit7:1; }; } @ 0x126;
__ext_io union { unsigned short TCNT5; struct { unsigned char TCNT5_Bit0:1, TCNT5_Bit1:1, TCNT5_Bit2:1, TCNT5_Bit3:1, TCNT5_Bit4:1, TCNT5_Bit5:1, TCNT5_Bit6:1, TCNT5_Bit7:1; unsigned char TCNT5_Bit8:1, TCNT5_Bit9:1, TCNT5_Bit10:1, TCNT5_Bit11:1, TCNT5_Bit12:1, TCNT5_Bit13:1, TCNT5_Bit14:1, TCNT5_Bit15:1; }; struct { unsigned char TCNT5L; unsigned char TCNT5H; }; struct { unsigned char TCNT5L_Bit0:1, TCNT5L_Bit1:1, TCNT5L_Bit2:1, TCNT5L_Bit3:1, TCNT5L_Bit4:1, TCNT5L_Bit5:1, TCNT5L_Bit6:1, TCNT5L_Bit7:1; unsigned char TCNT5H_Bit0:1, TCNT5H_Bit1:1, TCNT5H_Bit2:1, TCNT5H_Bit3:1, TCNT5H_Bit4:1, TCNT5H_Bit5:1, TCNT5H_Bit6:1, TCNT5H_Bit7:1; }; } @ 0x124;
__ext_io union { unsigned char TCCR5C; struct { unsigned char TCCR5C_Bit0:1, TCCR5C_Bit1:1, TCCR5C_Bit2:1, TCCR5C_Bit3:1, TCCR5C_Bit4:1, TCCR5C_Bit5:1, TCCR5C_Bit6:1, TCCR5C_Bit7:1; }; struct { unsigned char TCCR5C_Dummy0:1, TCCR5C_Dummy1:1, TCCR5C_Dummy2:1, TCCR5C_Dummy3:1, TCCR5C_Dummy4:1, TCCR5C_FOC5C:1, TCCR5C_FOC5B:1, TCCR5C_FOC5A:1; }; } @ 0x122;
__ext_io union { unsigned char TCCR5B; struct { unsigned char TCCR5B_Bit0:1, TCCR5B_Bit1:1, TCCR5B_Bit2:1, TCCR5B_Bit3:1, TCCR5B_Bit4:1, TCCR5B_Bit5:1, TCCR5B_Bit6:1, TCCR5B_Bit7:1; }; struct { unsigned char TCCR5B_CS50:1, TCCR5B_CS51:1, TCCR5B_CS52:1, TCCR5B_WGM52:1, TCCR5B_WGM53:1, TCCR5B_Dummy5:1, TCCR5B_ICES5:1, TCCR5B_ICNC5:1; }; } @ 0x121;
__ext_io union { unsigned char TCCR5A; struct { unsigned char TCCR5A_Bit0:1, TCCR5A_Bit1:1, TCCR5A_Bit2:1, TCCR5A_Bit3:1, TCCR5A_Bit4:1, TCCR5A_Bit5:1, TCCR5A_Bit6:1, TCCR5A_Bit7:1; }; struct { unsigned char TCCR5A_WGM50:1, TCCR5A_WGM51:1, TCCR5A_COM5C0:1, TCCR5A_COM5C1:1, TCCR5A_COM5B0:1, TCCR5A_COM5B1:1, TCCR5A_COM5A0:1, TCCR5A_COM5A1:1; }; } @ 0x120;
__ext_io union { unsigned char PORTL; struct { unsigned char PORTL_Bit0:1, PORTL_Bit1:1, PORTL_Bit2:1, PORTL_Bit3:1, PORTL_Bit4:1, PORTL_Bit5:1, PORTL_Bit6:1, PORTL_Bit7:1; }; struct { unsigned char PORTL_PORTL0:1, PORTL_PORTL1:1, PORTL_PORTL2:1, PORTL_PORTL3:1, PORTL_PORTL4:1, PORTL_PORTL5:1, PORTL_PORTL6:1, PORTL_PORTL7:1; }; } @ 0x10B;
__ext_io union { unsigned char DDRL; struct { unsigned char DDRL_Bit0:1, DDRL_Bit1:1, DDRL_Bit2:1, DDRL_Bit3:1, DDRL_Bit4:1, DDRL_Bit5:1, DDRL_Bit6:1, DDRL_Bit7:1; }; struct { unsigned char DDRL_DDL0:1, DDRL_DDL1:1, DDRL_DDL2:1, DDRL_DDL3:1, DDRL_DDL4:1, DDRL_DDL5:1, DDRL_DDL6:1, DDRL_DDL7:1; }; } @ 0x10A;
__ext_io union { unsigned char PINL; struct { unsigned char PINL_Bit0:1, PINL_Bit1:1, PINL_Bit2:1, PINL_Bit3:1, PINL_Bit4:1, PINL_Bit5:1, PINL_Bit6:1, PINL_Bit7:1; }; struct { unsigned char PINL_PINL0:1, PINL_PINL1:1, PINL_PINL2:1, PINL_PINL3:1, PINL_PINL4:1, PINL_PINL5:1, PINL_PINL6:1, PINL_PINL7:1; }; } @ 0x109;
__ext_io union { unsigned char PORTK; struct { unsigned char PORTK_Bit0:1, PORTK_Bit1:1, PORTK_Bit2:1, PORTK_Bit3:1, PORTK_Bit4:1, PORTK_Bit5:1, PORTK_Bit6:1, PORTK_Bit7:1; }; struct { unsigned char PORTK_PORTK0:1, PORTK_PORTK1:1, PORTK_PORTK2:1, PORTK_PORTK3:1, PORTK_PORTK4:1, PORTK_PORTK5:1, PORTK_PORTK6:1, PORTK_PORTK7:1; }; } @ 0x108;
__ext_io union { unsigned char DDRK; struct { unsigned char DDRK_Bit0:1, DDRK_Bit1:1, DDRK_Bit2:1, DDRK_Bit3:1, DDRK_Bit4:1, DDRK_Bit5:1, DDRK_Bit6:1, DDRK_Bit7:1; }; struct { unsigned char DDRK_DDK0:1, DDRK_DDK1:1, DDRK_DDK2:1, DDRK_DDK3:1, DDRK_DDK4:1, DDRK_DDK5:1, DDRK_DDK6:1, DDRK_DDK7:1; }; } @ 0x107;
__ext_io union { unsigned char PINK; struct { unsigned char PINK_Bit0:1, PINK_Bit1:1, PINK_Bit2:1, PINK_Bit3:1, PINK_Bit4:1, PINK_Bit5:1, PINK_Bit6:1, PINK_Bit7:1; }; struct { unsigned char PINK_PINK0:1, PINK_PINK1:1, PINK_PINK2:1, PINK_PINK3:1, PINK_PINK4:1, PINK_PINK5:1, PINK_PINK6:1, PINK_PINK7:1; }; } @ 0x106;
__ext_io union { unsigned char PORTJ; struct { unsigned char PORTJ_Bit0:1, PORTJ_Bit1:1, PORTJ_Bit2:1, PORTJ_Bit3:1, PORTJ_Bit4:1, PORTJ_Bit5:1, PORTJ_Bit6:1, PORTJ_Bit7:1; }; struct { unsigned char PORTJ_PORTJ0:1, PORTJ_PORTJ1:1, PORTJ_PORTJ2:1, PORTJ_PORTJ3:1, PORTJ_PORTJ4:1, PORTJ_PORTJ5:1, PORTJ_PORTJ6:1, PORTJ_PORTJ7:1; }; } @ 0x105;
__ext_io union { unsigned char DDRJ; struct { unsigned char DDRJ_Bit0:1, DDRJ_Bit1:1, DDRJ_Bit2:1, DDRJ_Bit3:1, DDRJ_Bit4:1, DDRJ_Bit5:1, DDRJ_Bit6:1, DDRJ_Bit7:1; }; struct { unsigned char DDRJ_DDJ0:1, DDRJ_DDJ1:1, DDRJ_DDJ2:1, DDRJ_DDJ3:1, DDRJ_DDJ4:1, DDRJ_DDJ5:1, DDRJ_DDJ6:1, DDRJ_DDJ7:1; }; } @ 0x104;
__ext_io union { unsigned char PINJ; struct { unsigned char PINJ_Bit0:1, PINJ_Bit1:1, PINJ_Bit2:1, PINJ_Bit3:1, PINJ_Bit4:1, PINJ_Bit5:1, PINJ_Bit6:1, PINJ_Bit7:1; }; struct { unsigned char PINJ_PINJ0:1, PINJ_PINJ1:1, PINJ_PINJ2:1, PINJ_PINJ3:1, PINJ_PINJ4:1, PINJ_PINJ5:1, PINJ_PINJ6:1, PINJ_PINJ7:1; }; } @ 0x103;
__ext_io union { unsigned char PORTH; struct { unsigned char PORTH_Bit0:1, PORTH_Bit1:1, PORTH_Bit2:1, PORTH_Bit3:1, PORTH_Bit4:1, PORTH_Bit5:1, PORTH_Bit6:1, PORTH_Bit7:1; }; struct { unsigned char PORTH_PORTH0:1, PORTH_PORTH1:1, PORTH_PORTH2:1, PORTH_PORTH3:1, PORTH_PORTH4:1, PORTH_PORTH5:1, PORTH_PORTH6:1, PORTH_PORTH7:1; }; } @ 0x102;
__ext_io union { unsigned char DDRH; struct { unsigned char DDRH_Bit0:1, DDRH_Bit1:1, DDRH_Bit2:1, DDRH_Bit3:1, DDRH_Bit4:1, DDRH_Bit5:1, DDRH_Bit6:1, DDRH_Bit7:1; }; struct { unsigned char DDRH_DDH0:1, DDRH_DDH1:1, DDRH_DDH2:1, DDRH_DDH3:1, DDRH_DDH4:1, DDRH_DDH5:1, DDRH_DDH6:1, DDRH_DDH7:1; }; } @ 0x101;
__ext_io union { unsigned char PINH; struct { unsigned char PINH_Bit0:1, PINH_Bit1:1, PINH_Bit2:1, PINH_Bit3:1, PINH_Bit4:1, PINH_Bit5:1, PINH_Bit6:1, PINH_Bit7:1; }; struct { unsigned char PINH_PINH0:1, PINH_PINH1:1, PINH_PINH2:1, PINH_PINH3:1, PINH_PINH4:1, PINH_PINH5:1, PINH_PINH6:1, PINH_PINH7:1; }; } @ 0x100;

__io union { unsigned char UDR2; struct { unsigned char UDR2_Bit0:1, UDR2_Bit1:1, UDR2_Bit2:1, UDR2_Bit3:1, UDR2_Bit4:1, UDR2_Bit5:1, UDR2_Bit6:1, UDR2_Bit7:1; }; } @ 0xD6;
__io union { unsigned short UBRR2; struct { unsigned char UBRR2_Bit0:1, UBRR2_Bit1:1, UBRR2_Bit2:1, UBRR2_Bit3:1, UBRR2_Bit4:1, UBRR2_Bit5:1, UBRR2_Bit6:1, UBRR2_Bit7:1; unsigned char UBRR2_Bit8:1, UBRR2_Bit9:1, UBRR2_Bit10:1, UBRR2_Bit11:1, UBRR2_Bit12:1, UBRR2_Bit13:1, UBRR2_Bit14:1, UBRR2_Bit15:1; }; struct { unsigned char UBRR2L; unsigned char UBRR2H; }; struct { unsigned char UBRR2L_Bit0:1, UBRR2L_Bit1:1, UBRR2L_Bit2:1, UBRR2L_Bit3:1, UBRR2L_Bit4:1, UBRR2L_Bit5:1, UBRR2L_Bit6:1, UBRR2L_Bit7:1; unsigned char UBRR2H_Bit0:1, UBRR2H_Bit1:1, UBRR2H_Bit2:1, UBRR2H_Bit3:1, UBRR2H_Bit4:1, UBRR2H_Bit5:1, UBRR2H_Bit6:1, UBRR2H_Bit7:1; }; } @ 0xD4;
__io union { unsigned char UCSR2C; struct { unsigned char UCSR2C_Bit0:1, UCSR2C_Bit1:1, UCSR2C_Bit2:1, UCSR2C_Bit3:1, UCSR2C_Bit4:1, UCSR2C_Bit5:1, UCSR2C_Bit6:1, UCSR2C_Bit7:1; }; struct { unsigned char UCSR2C_UCPOL2:1, UCSR2C_UCSZ20:1, UCSR2C_UCSZ21:1, UCSR2C_USBS2:1, UCSR2C_UPM20:1, UCSR2C_UPM21:1, UCSR2C_UMSEL20:1, UCSR2C_UMSEL21:1; }; struct{ unsigned char :5; unsigned char UCSR2C_UDORD2:1; unsigned char UCSR2C_UCPHA2:1; unsigned char :1;}; } @ 0xD2;
__io union { unsigned char UCSR2B; struct { unsigned char UCSR2B_Bit0:1, UCSR2B_Bit1:1, UCSR2B_Bit2:1, UCSR2B_Bit3:1, UCSR2B_Bit4:1, UCSR2B_Bit5:1, UCSR2B_Bit6:1, UCSR2B_Bit7:1; }; struct { unsigned char UCSR2B_TXB82:1, UCSR2B_RXB82:1, UCSR2B_UCSZ22:1, UCSR2B_TXEN2:1, UCSR2B_RXEN2:1, UCSR2B_UDRIE2:1, UCSR2B_TXCIE2:1, UCSR2B_RXCIE2:1; }; } @ 0xD1;
__io union { unsigned char UCSR2A; struct { unsigned char UCSR2A_Bit0:1, UCSR2A_Bit1:1, UCSR2A_Bit2:1, UCSR2A_Bit3:1, UCSR2A_Bit4:1, UCSR2A_Bit5:1, UCSR2A_Bit6:1, UCSR2A_Bit7:1; }; struct { unsigned char UCSR2A_MPCM2:1, UCSR2A_U2X2:1, UCSR2A_UPE2:1, UCSR2A_DOR2:1, UCSR2A_FE2:1, UCSR2A_UDRE2:1, UCSR2A_TXC2:1, UCSR2A_RXC2:1; }; } @ 0xD0;
__io union { unsigned char UDR1; struct { unsigned char UDR1_Bit0:1, UDR1_Bit1:1, UDR1_Bit2:1, UDR1_Bit3:1, UDR1_Bit4:1, UDR1_Bit5:1, UDR1_Bit6:1, UDR1_Bit7:1; }; } @ 0xCE;
__io union { unsigned short UBRR1; struct { unsigned char UBRR1_Bit0:1, UBRR1_Bit1:1, UBRR1_Bit2:1, UBRR1_Bit3:1, UBRR1_Bit4:1, UBRR1_Bit5:1, UBRR1_Bit6:1, UBRR1_Bit7:1; unsigned char UBRR1_Bit8:1, UBRR1_Bit9:1, UBRR1_Bit10:1, UBRR1_Bit11:1, UBRR1_Bit12:1, UBRR1_Bit13:1, UBRR1_Bit14:1, UBRR1_Bit15:1; }; struct { unsigned char UBRR1L; unsigned char UBRR1H; }; struct { unsigned char UBRR1L_Bit0:1, UBRR1L_Bit1:1, UBRR1L_Bit2:1, UBRR1L_Bit3:1, UBRR1L_Bit4:1, UBRR1L_Bit5:1, UBRR1L_Bit6:1, UBRR1L_Bit7:1; unsigned char UBRR1H_Bit0:1, UBRR1H_Bit1:1, UBRR1H_Bit2:1, UBRR1H_Bit3:1, UBRR1H_Bit4:1, UBRR1H_Bit5:1, UBRR1H_Bit6:1, UBRR1H_Bit7:1; }; } @ 0xCC;
__io union { unsigned char UCSR1C; struct { unsigned char UCSR1C_Bit0:1, UCSR1C_Bit1:1, UCSR1C_Bit2:1, UCSR1C_Bit3:1, UCSR1C_Bit4:1, UCSR1C_Bit5:1, UCSR1C_Bit6:1, UCSR1C_Bit7:1; }; struct { unsigned char UCSR1C_UCPOL1:1, UCSR1C_UCSZ10:1, UCSR1C_UCSZ11:1, UCSR1C_USBS1:1, UCSR1C_UPM10:1, UCSR1C_UPM11:1, UCSR1C_UMSEL10:1, UCSR1C_UMSEL11:1; }; struct{ unsigned char :5; unsigned char UCSR1C_UDORD1:1; unsigned char UCSR1C_UCPHA1:1; unsigned char :1;}; } @ 0xCA;
__io union { unsigned char UCSR1B; struct { unsigned char UCSR1B_Bit0:1, UCSR1B_Bit1:1, UCSR1B_Bit2:1, UCSR1B_Bit3:1, UCSR1B_Bit4:1, UCSR1B_Bit5:1, UCSR1B_Bit6:1, UCSR1B_Bit7:1; }; struct { unsigned char UCSR1B_TXB81:1, UCSR1B_RXB81:1, UCSR1B_UCSZ12:1, UCSR1B_TXEN1:1, UCSR1B_RXEN1:1, UCSR1B_UDRIE1:1, UCSR1B_TXCIE1:1, UCSR1B_RXCIE1:1; }; } @ 0xC9;
__io union { unsigned char UCSR1A; struct { unsigned char UCSR1A_Bit0:1, UCSR1A_Bit1:1, UCSR1A_Bit2:1, UCSR1A_Bit3:1, UCSR1A_Bit4:1, UCSR1A_Bit5:1, UCSR1A_Bit6:1, UCSR1A_Bit7:1; }; struct { unsigned char UCSR1A_MPCM1:1, UCSR1A_U2X1:1, UCSR1A_UPE1:1, UCSR1A_DOR1:1, UCSR1A_FE1:1, UCSR1A_UDRE1:1, UCSR1A_TXC1:1, UCSR1A_RXC1:1; }; } @ 0xC8;
__io union { unsigned char UDR0; struct { unsigned char UDR0_Bit0:1, UDR0_Bit1:1, UDR0_Bit2:1, UDR0_Bit3:1, UDR0_Bit4:1, UDR0_Bit5:1, UDR0_Bit6:1, UDR0_Bit7:1; }; } @ 0xC6;
__io union { unsigned short UBRR0; struct { unsigned char UBRR0_Bit0:1, UBRR0_Bit1:1, UBRR0_Bit2:1, UBRR0_Bit3:1, UBRR0_Bit4:1, UBRR0_Bit5:1, UBRR0_Bit6:1, UBRR0_Bit7:1; unsigned char UBRR0_Bit8:1, UBRR0_Bit9:1, UBRR0_Bit10:1, UBRR0_Bit11:1, UBRR0_Bit12:1, UBRR0_Bit13:1, UBRR0_Bit14:1, UBRR0_Bit15:1; }; struct { unsigned char UBRR0L; unsigned char UBRR0H; }; struct { unsigned char UBRR0L_Bit0:1, UBRR0L_Bit1:1, UBRR0L_Bit2:1, UBRR0L_Bit3:1, UBRR0L_Bit4:1, UBRR0L_Bit5:1, UBRR0L_Bit6:1, UBRR0L_Bit7:1; unsigned char UBRR0H_Bit0:1, UBRR0H_Bit1:1, UBRR0H_Bit2:1, UBRR0H_Bit3:1, UBRR0H_Bit4:1, UBRR0H_Bit5:1, UBRR0H_Bit6:1, UBRR0H_Bit7:1; }; } @ 0xC4;
__io union { unsigned char UCSR0C; struct { unsigned char UCSR0C_Bit0:1, UCSR0C_Bit1:1, UCSR0C_Bit2:1, UCSR0C_Bit3:1, UCSR0C_Bit4:1, UCSR0C_Bit5:1, UCSR0C_Bit6:1, UCSR0C_Bit7:1; }; struct { unsigned char UCSR0C_UCPOL0:1, UCSR0C_UCSZ00:1, UCSR0C_UCSZ01:1, UCSR0C_USBS0:1, UCSR0C_UPM00:1, UCSR0C_UPM01:1, UCSR0C_UMSEL00:1, UCSR0C_UMSEL01:1; }; struct{ unsigned char :5; unsigned char UCSR0C_UDORD0:1; unsigned char UCSR0C_UCPHA0:1; unsigned char :1;}; } @ 0xC2;
__io union { unsigned char UCSR0B; struct { unsigned char UCSR0B_Bit0:1, UCSR0B_Bit1:1, UCSR0B_Bit2:1, UCSR0B_Bit3:1, UCSR0B_Bit4:1, UCSR0B_Bit5:1, UCSR0B_Bit6:1, UCSR0B_Bit7:1; }; struct { unsigned char UCSR0B_TXB80:1, UCSR0B_RXB80:1, UCSR0B_UCSZ02:1, UCSR0B_TXEN0:1, UCSR0B_RXEN0:1, UCSR0B_UDRIE0:1, UCSR0B_TXCIE0:1, UCSR0B_RXCIE0:1; }; } @ 0xC1;
__io union { unsigned char UCSR0A; struct { unsigned char UCSR0A_Bit0:1, UCSR0A_Bit1:1, UCSR0A_Bit2:1, UCSR0A_Bit3:1, UCSR0A_Bit4:1, UCSR0A_Bit5:1, UCSR0A_Bit6:1, UCSR0A_Bit7:1; }; struct { unsigned char UCSR0A_MPCM0:1, UCSR0A_U2X0:1, UCSR0A_UPE0:1, UCSR0A_DOR0:1, UCSR0A_FE0:1, UCSR0A_UDRE0:1, UCSR0A_TXC0:1, UCSR0A_RXC0:1; }; } @ 0xC0;
__io union { unsigned char TWAMR; struct { unsigned char TWAMR_Bit0:1, TWAMR_Bit1:1, TWAMR_Bit2:1, TWAMR_Bit3:1, TWAMR_Bit4:1, TWAMR_Bit5:1, TWAMR_Bit6:1, TWAMR_Bit7:1; }; struct { unsigned char TWAMR_Dummy0:1, TWAMR_TWAM0:1, TWAMR_TWAM1:1, TWAMR_TWAM2:1, TWAMR_TWAM3:1, TWAMR_TWAM4:1, TWAMR_TWAM5:1, TWAMR_TWAM6:1; }; } @ 0xBD;
__io union { unsigned char TWCR; struct { unsigned char TWCR_Bit0:1, TWCR_Bit1:1, TWCR_Bit2:1, TWCR_Bit3:1, TWCR_Bit4:1, TWCR_Bit5:1, TWCR_Bit6:1, TWCR_Bit7:1; }; struct { unsigned char TWCR_TWIE:1, TWCR_Dummy1:1, TWCR_TWEN:1, TWCR_TWWC:1, TWCR_TWSTO:1, TWCR_TWSTA:1, TWCR_TWEA:1, TWCR_TWINT:1; }; } @ 0xBC;
__io union { unsigned char TWDR; struct { unsigned char TWDR_Bit0:1, TWDR_Bit1:1, TWDR_Bit2:1, TWDR_Bit3:1, TWDR_Bit4:1, TWDR_Bit5:1, TWDR_Bit6:1, TWDR_Bit7:1; }; } @ 0xBB;
__io union { unsigned char TWAR; struct { unsigned char TWAR_Bit0:1, TWAR_Bit1:1, TWAR_Bit2:1, TWAR_Bit3:1, TWAR_Bit4:1, TWAR_Bit5:1, TWAR_Bit6:1, TWAR_Bit7:1; }; struct { unsigned char TWAR_TWGCE:1, TWAR_TWA0:1, TWAR_TWA1:1, TWAR_TWA2:1, TWAR_TWA3:1, TWAR_TWA4:1, TWAR_TWA5:1, TWAR_TWA6:1; }; } @ 0xBA;
__io union { unsigned char TWSR; struct { unsigned char TWSR_Bit0:1, TWSR_Bit1:1, TWSR_Bit2:1, TWSR_Bit3:1, TWSR_Bit4:1, TWSR_Bit5:1, TWSR_Bit6:1, TWSR_Bit7:1; }; struct { unsigned char TWSR_TWPS0:1, TWSR_TWPS1:1, TWSR_Dummy2:1, TWSR_TWS3:1, TWSR_TWS4:1, TWSR_TWS5:1, TWSR_TWS6:1, TWSR_TWS7:1; }; } @ 0xB9;
__io union { unsigned char TWBR; struct { unsigned char TWBR_Bit0:1, TWBR_Bit1:1, TWBR_Bit2:1, TWBR_Bit3:1, TWBR_Bit4:1, TWBR_Bit5:1, TWBR_Bit6:1, TWBR_Bit7:1; }; } @ 0xB8;
__io union { unsigned char ASSR; struct { unsigned char ASSR_Bit0:1, ASSR_Bit1:1, ASSR_Bit2:1, ASSR_Bit3:1, ASSR_Bit4:1, ASSR_Bit5:1, ASSR_Bit6:1, ASSR_Bit7:1; }; struct { unsigned char ASSR_TCR2BUB:1, ASSR_TCR2AUB:1, ASSR_OCR2BUB:1, ASSR_OCR2AUB:1, ASSR_TCN2UB:1, ASSR_AS2:1, ASSR_EXCLK:1, ASSR_Dummy7:1; }; } @ 0xB6;
__io union { unsigned char OCR2B; struct { unsigned char OCR2B_Bit0:1, OCR2B_Bit1:1, OCR2B_Bit2:1, OCR2B_Bit3:1, OCR2B_Bit4:1, OCR2B_Bit5:1, OCR2B_Bit6:1, OCR2B_Bit7:1; }; } @ 0xB4;
__io union { unsigned char OCR2A; struct { unsigned char OCR2A_Bit0:1, OCR2A_Bit1:1, OCR2A_Bit2:1, OCR2A_Bit3:1, OCR2A_Bit4:1, OCR2A_Bit5:1, OCR2A_Bit6:1, OCR2A_Bit7:1; }; } @ 0xB3;
__io union { unsigned char TCNT2; struct { unsigned char TCNT2_Bit0:1, TCNT2_Bit1:1, TCNT2_Bit2:1, TCNT2_Bit3:1, TCNT2_Bit4:1, TCNT2_Bit5:1, TCNT2_Bit6:1, TCNT2_Bit7:1; }; } @ 0xB2;
__io union { unsigned char TCCR2B; struct { unsigned char TCCR2B_Bit0:1, TCCR2B_Bit1:1, TCCR2B_Bit2:1, TCCR2B_Bit3:1, TCCR2B_Bit4:1, TCCR2B_Bit5:1, TCCR2B_Bit6:1, TCCR2B_Bit7:1; }; struct { unsigned char TCCR2B_CS20:1, TCCR2B_CS21:1, TCCR2B_CS22:1, TCCR2B_WGM22:1, TCCR2B_Dummy4:1, TCCR2B_Dummy5:1, TCCR2B_FOC2B:1, TCCR2B_FOC2A:1; }; } @ 0xB1;
__io union { unsigned char TCCR2A; struct { unsigned char TCCR2A_Bit0:1, TCCR2A_Bit1:1, TCCR2A_Bit2:1, TCCR2A_Bit3:1, TCCR2A_Bit4:1, TCCR2A_Bit5:1, TCCR2A_Bit6:1, TCCR2A_Bit7:1; }; struct { unsigned char TCCR2A_WGM20:1, TCCR2A_WGM21:1, TCCR2A_Dummy2:1, TCCR2A_Dummy3:1, TCCR2A_COM2B0:1, TCCR2A_COM2B1:1, TCCR2A_COM2A0:1, TCCR2A_COM2A1:1; }; } @ 0xB0;
__io union { unsigned short OCR4C; struct { unsigned char OCR4C_Bit0:1, OCR4C_Bit1:1, OCR4C_Bit2:1, OCR4C_Bit3:1, OCR4C_Bit4:1, OCR4C_Bit5:1, OCR4C_Bit6:1, OCR4C_Bit7:1; unsigned char OCR4C_Bit8:1, OCR4C_Bit9:1, OCR4C_Bit10:1, OCR4C_Bit11:1, OCR4C_Bit12:1, OCR4C_Bit13:1, OCR4C_Bit14:1, OCR4C_Bit15:1; }; struct { unsigned char OCR4CL; unsigned char OCR4CH; }; struct { unsigned char OCR4CL_Bit0:1, OCR4CL_Bit1:1, OCR4CL_Bit2:1, OCR4CL_Bit3:1, OCR4CL_Bit4:1, OCR4CL_Bit5:1, OCR4CL_Bit6:1, OCR4CL_Bit7:1; unsigned char OCR4CH_Bit0:1, OCR4CH_Bit1:1, OCR4CH_Bit2:1, OCR4CH_Bit3:1, OCR4CH_Bit4:1, OCR4CH_Bit5:1, OCR4CH_Bit6:1, OCR4CH_Bit7:1; }; } @ 0xAC;
__io union { unsigned short OCR4B; struct { unsigned char OCR4B_Bit0:1, OCR4B_Bit1:1, OCR4B_Bit2:1, OCR4B_Bit3:1, OCR4B_Bit4:1, OCR4B_Bit5:1, OCR4B_Bit6:1, OCR4B_Bit7:1; unsigned char OCR4B_Bit8:1, OCR4B_Bit9:1, OCR4B_Bit10:1, OCR4B_Bit11:1, OCR4B_Bit12:1, OCR4B_Bit13:1, OCR4B_Bit14:1, OCR4B_Bit15:1; }; struct { unsigned char OCR4BL; unsigned char OCR4BH; }; struct { unsigned char OCR4BL_Bit0:1, OCR4BL_Bit1:1, OCR4BL_Bit2:1, OCR4BL_Bit3:1, OCR4BL_Bit4:1, OCR4BL_Bit5:1, OCR4BL_Bit6:1, OCR4BL_Bit7:1; unsigned char OCR4BH_Bit0:1, OCR4BH_Bit1:1, OCR4BH_Bit2:1, OCR4BH_Bit3:1, OCR4BH_Bit4:1, OCR4BH_Bit5:1, OCR4BH_Bit6:1, OCR4BH_Bit7:1; }; } @ 0xAA;
__io union { unsigned short OCR4A; struct { unsigned char OCR4A_Bit0:1, OCR4A_Bit1:1, OCR4A_Bit2:1, OCR4A_Bit3:1, OCR4A_Bit4:1, OCR4A_Bit5:1, OCR4A_Bit6:1, OCR4A_Bit7:1; unsigned char OCR4A_Bit8:1, OCR4A_Bit9:1, OCR4A_Bit10:1, OCR4A_Bit11:1, OCR4A_Bit12:1, OCR4A_Bit13:1, OCR4A_Bit14:1, OCR4A_Bit15:1; }; struct { unsigned char OCR4AL; unsigned char OCR4AH; }; struct { unsigned char OCR4AL_Bit0:1, OCR4AL_Bit1:1, OCR4AL_Bit2:1, OCR4AL_Bit3:1, OCR4AL_Bit4:1, OCR4AL_Bit5:1, OCR4AL_Bit6:1, OCR4AL_Bit7:1; unsigned char OCR4AH_Bit0:1, OCR4AH_Bit1:1, OCR4AH_Bit2:1, OCR4AH_Bit3:1, OCR4AH_Bit4:1, OCR4AH_Bit5:1, OCR4AH_Bit6:1, OCR4AH_Bit7:1; }; } @ 0xA8;
__io union { unsigned short ICR4; struct { unsigned char ICR4_Bit0:1, ICR4_Bit1:1, ICR4_Bit2:1, ICR4_Bit3:1, ICR4_Bit4:1, ICR4_Bit5:1, ICR4_Bit6:1, ICR4_Bit7:1; unsigned char ICR4_Bit8:1, ICR4_Bit9:1, ICR4_Bit10:1, ICR4_Bit11:1, ICR4_Bit12:1, ICR4_Bit13:1, ICR4_Bit14:1, ICR4_Bit15:1; }; struct { unsigned char ICR4L; unsigned char ICR4H; }; struct { unsigned char ICR4L_Bit0:1, ICR4L_Bit1:1, ICR4L_Bit2:1, ICR4L_Bit3:1, ICR4L_Bit4:1, ICR4L_Bit5:1, ICR4L_Bit6:1, ICR4L_Bit7:1; unsigned char ICR4H_Bit0:1, ICR4H_Bit1:1, ICR4H_Bit2:1, ICR4H_Bit3:1, ICR4H_Bit4:1, ICR4H_Bit5:1, ICR4H_Bit6:1, ICR4H_Bit7:1; }; } @ 0xA6;
__io union { unsigned short TCNT4; struct { unsigned char TCNT4_Bit0:1, TCNT4_Bit1:1, TCNT4_Bit2:1, TCNT4_Bit3:1, TCNT4_Bit4:1, TCNT4_Bit5:1, TCNT4_Bit6:1, TCNT4_Bit7:1; unsigned char TCNT4_Bit8:1, TCNT4_Bit9:1, TCNT4_Bit10:1, TCNT4_Bit11:1, TCNT4_Bit12:1, TCNT4_Bit13:1, TCNT4_Bit14:1, TCNT4_Bit15:1; }; struct { unsigned char TCNT4L; unsigned char TCNT4H; }; struct { unsigned char TCNT4L_Bit0:1, TCNT4L_Bit1:1, TCNT4L_Bit2:1, TCNT4L_Bit3:1, TCNT4L_Bit4:1, TCNT4L_Bit5:1, TCNT4L_Bit6:1, TCNT4L_Bit7:1; unsigned char TCNT4H_Bit0:1, TCNT4H_Bit1:1, TCNT4H_Bit2:1, TCNT4H_Bit3:1, TCNT4H_Bit4:1, TCNT4H_Bit5:1, TCNT4H_Bit6:1, TCNT4H_Bit7:1; }; } @ 0xA4;
__io union { unsigned char TCCR4C; struct { unsigned char TCCR4C_Bit0:1, TCCR4C_Bit1:1, TCCR4C_Bit2:1, TCCR4C_Bit3:1, TCCR4C_Bit4:1, TCCR4C_Bit5:1, TCCR4C_Bit6:1, TCCR4C_Bit7:1; }; struct { unsigned char TCCR4C_Dummy0:1, TCCR4C_Dummy1:1, TCCR4C_Dummy2:1, TCCR4C_Dummy3:1, TCCR4C_Dummy4:1, TCCR4C_FOC4C:1, TCCR4C_FOC4B:1, TCCR4C_FOC4A:1; }; } @ 0xA2;
__io union { unsigned char TCCR4B; struct { unsigned char TCCR4B_Bit0:1, TCCR4B_Bit1:1, TCCR4B_Bit2:1, TCCR4B_Bit3:1, TCCR4B_Bit4:1, TCCR4B_Bit5:1, TCCR4B_Bit6:1, TCCR4B_Bit7:1; }; struct { unsigned char TCCR4B_CS40:1, TCCR4B_CS41:1, TCCR4B_CS42:1, TCCR4B_WGM42:1, TCCR4B_WGM43:1, TCCR4B_Dummy5:1, TCCR4B_ICES4:1, TCCR4B_ICNC4:1; }; } @ 0xA1;
__io union { unsigned char TCCR4A; struct { unsigned char TCCR4A_Bit0:1, TCCR4A_Bit1:1, TCCR4A_Bit2:1, TCCR4A_Bit3:1, TCCR4A_Bit4:1, TCCR4A_Bit5:1, TCCR4A_Bit6:1, TCCR4A_Bit7:1; }; struct { unsigned char TCCR4A_WGM40:1, TCCR4A_WGM41:1, TCCR4A_COM4C0:1, TCCR4A_COM4C1:1, TCCR4A_COM4B0:1, TCCR4A_COM4B1:1, TCCR4A_COM4A0:1, TCCR4A_COM4A1:1; }; } @ 0xA0;
__io union { unsigned short OCR3C; struct { unsigned char OCR3C_Bit0:1, OCR3C_Bit1:1, OCR3C_Bit2:1, OCR3C_Bit3:1, OCR3C_Bit4:1, OCR3C_Bit5:1, OCR3C_Bit6:1, OCR3C_Bit7:1; unsigned char OCR3C_Bit8:1, OCR3C_Bit9:1, OCR3C_Bit10:1, OCR3C_Bit11:1, OCR3C_Bit12:1, OCR3C_Bit13:1, OCR3C_Bit14:1, OCR3C_Bit15:1; }; struct { unsigned char OCR3CL; unsigned char OCR3CH; }; struct { unsigned char OCR3CL_Bit0:1, OCR3CL_Bit1:1, OCR3CL_Bit2:1, OCR3CL_Bit3:1, OCR3CL_Bit4:1, OCR3CL_Bit5:1, OCR3CL_Bit6:1, OCR3CL_Bit7:1; unsigned char OCR3CH_Bit0:1, OCR3CH_Bit1:1, OCR3CH_Bit2:1, OCR3CH_Bit3:1, OCR3CH_Bit4:1, OCR3CH_Bit5:1, OCR3CH_Bit6:1, OCR3CH_Bit7:1; }; } @ 0x9C;
__io union { unsigned short OCR3B; struct { unsigned char OCR3B_Bit0:1, OCR3B_Bit1:1, OCR3B_Bit2:1, OCR3B_Bit3:1, OCR3B_Bit4:1, OCR3B_Bit5:1, OCR3B_Bit6:1, OCR3B_Bit7:1; unsigned char OCR3B_Bit8:1, OCR3B_Bit9:1, OCR3B_Bit10:1, OCR3B_Bit11:1, OCR3B_Bit12:1, OCR3B_Bit13:1, OCR3B_Bit14:1, OCR3B_Bit15:1; }; struct { unsigned char OCR3BL; unsigned char OCR3BH; }; struct { unsigned char OCR3BL_Bit0:1, OCR3BL_Bit1:1, OCR3BL_Bit2:1, OCR3BL_Bit3:1, OCR3BL_Bit4:1, OCR3BL_Bit5:1, OCR3BL_Bit6:1, OCR3BL_Bit7:1; unsigned char OCR3BH_Bit0:1, OCR3BH_Bit1:1, OCR3BH_Bit2:1, OCR3BH_Bit3:1, OCR3BH_Bit4:1, OCR3BH_Bit5:1, OCR3BH_Bit6:1, OCR3BH_Bit7:1; }; } @ 0x9A;
__io union { unsigned short OCR3A; struct { unsigned char OCR3A_Bit0:1, OCR3A_Bit1:1, OCR3A_Bit2:1, OCR3A_Bit3:1, OCR3A_Bit4:1, OCR3A_Bit5:1, OCR3A_Bit6:1, OCR3A_Bit7:1; unsigned char OCR3A_Bit8:1, OCR3A_Bit9:1, OCR3A_Bit10:1, OCR3A_Bit11:1, OCR3A_Bit12:1, OCR3A_Bit13:1, OCR3A_Bit14:1, OCR3A_Bit15:1; }; struct { unsigned char OCR3AL; unsigned char OCR3AH; }; struct { unsigned char OCR3AL_Bit0:1, OCR3AL_Bit1:1, OCR3AL_Bit2:1, OCR3AL_Bit3:1, OCR3AL_Bit4:1, OCR3AL_Bit5:1, OCR3AL_Bit6:1, OCR3AL_Bit7:1; unsigned char OCR3AH_Bit0:1, OCR3AH_Bit1:1, OCR3AH_Bit2:1, OCR3AH_Bit3:1, OCR3AH_Bit4:1, OCR3AH_Bit5:1, OCR3AH_Bit6:1, OCR3AH_Bit7:1; }; } @ 0x98;
__io union { unsigned short ICR3; struct { unsigned char ICR3_Bit0:1, ICR3_Bit1:1, ICR3_Bit2:1, ICR3_Bit3:1, ICR3_Bit4:1, ICR3_Bit5:1, ICR3_Bit6:1, ICR3_Bit7:1; unsigned char ICR3_Bit8:1, ICR3_Bit9:1, ICR3_Bit10:1, ICR3_Bit11:1, ICR3_Bit12:1, ICR3_Bit13:1, ICR3_Bit14:1, ICR3_Bit15:1; }; struct { unsigned char ICR3L; unsigned char ICR3H; }; struct { unsigned char ICR3L_Bit0:1, ICR3L_Bit1:1, ICR3L_Bit2:1, ICR3L_Bit3:1, ICR3L_Bit4:1, ICR3L_Bit5:1, ICR3L_Bit6:1, ICR3L_Bit7:1; unsigned char ICR3H_Bit0:1, ICR3H_Bit1:1, ICR3H_Bit2:1, ICR3H_Bit3:1, ICR3H_Bit4:1, ICR3H_Bit5:1, ICR3H_Bit6:1, ICR3H_Bit7:1; }; } @ 0x96;
__io union { unsigned short TCNT3; struct { unsigned char TCNT3_Bit0:1, TCNT3_Bit1:1, TCNT3_Bit2:1, TCNT3_Bit3:1, TCNT3_Bit4:1, TCNT3_Bit5:1, TCNT3_Bit6:1, TCNT3_Bit7:1; unsigned char TCNT3_Bit8:1, TCNT3_Bit9:1, TCNT3_Bit10:1, TCNT3_Bit11:1, TCNT3_Bit12:1, TCNT3_Bit13:1, TCNT3_Bit14:1, TCNT3_Bit15:1; }; struct { unsigned char TCNT3L; unsigned char TCNT3H; }; struct { unsigned char TCNT3L_Bit0:1, TCNT3L_Bit1:1, TCNT3L_Bit2:1, TCNT3L_Bit3:1, TCNT3L_Bit4:1, TCNT3L_Bit5:1, TCNT3L_Bit6:1, TCNT3L_Bit7:1; unsigned char TCNT3H_Bit0:1, TCNT3H_Bit1:1, TCNT3H_Bit2:1, TCNT3H_Bit3:1, TCNT3H_Bit4:1, TCNT3H_Bit5:1, TCNT3H_Bit6:1, TCNT3H_Bit7:1; }; } @ 0x94;
__io union { unsigned char TCCR3C; struct { unsigned char TCCR3C_Bit0:1, TCCR3C_Bit1:1, TCCR3C_Bit2:1, TCCR3C_Bit3:1, TCCR3C_Bit4:1, TCCR3C_Bit5:1, TCCR3C_Bit6:1, TCCR3C_Bit7:1; }; struct { unsigned char TCCR3C_Dummy0:1, TCCR3C_Dummy1:1, TCCR3C_Dummy2:1, TCCR3C_Dummy3:1, TCCR3C_Dummy4:1, TCCR3C_FOC3C:1, TCCR3C_FOC3B:1, TCCR3C_FOC3A:1; }; } @ 0x92;
__io union { unsigned char TCCR3B; struct { unsigned char TCCR3B_Bit0:1, TCCR3B_Bit1:1, TCCR3B_Bit2:1, TCCR3B_Bit3:1, TCCR3B_Bit4:1, TCCR3B_Bit5:1, TCCR3B_Bit6:1, TCCR3B_Bit7:1; }; struct { unsigned char TCCR3B_CS30:1, TCCR3B_CS31:1, TCCR3B_CS32:1, TCCR3B_WGM32:1, TCCR3B_WGM33:1, TCCR3B_Dummy5:1, TCCR3B_ICES3:1, TCCR3B_ICNC3:1; }; } @ 0x91;
__io union { unsigned char TCCR3A; struct { unsigned char TCCR3A_Bit0:1, TCCR3A_Bit1:1, TCCR3A_Bit2:1, TCCR3A_Bit3:1, TCCR3A_Bit4:1, TCCR3A_Bit5:1, TCCR3A_Bit6:1, TCCR3A_Bit7:1; }; struct { unsigned char TCCR3A_WGM30:1, TCCR3A_WGM31:1, TCCR3A_COM3C0:1, TCCR3A_COM3C1:1, TCCR3A_COM3B0:1, TCCR3A_COM3B1:1, TCCR3A_COM3A0:1, TCCR3A_COM3A1:1; }; } @ 0x90;
__io union { unsigned short OCR1C; struct { unsigned char OCR1C_Bit0:1, OCR1C_Bit1:1, OCR1C_Bit2:1, OCR1C_Bit3:1, OCR1C_Bit4:1, OCR1C_Bit5:1, OCR1C_Bit6:1, OCR1C_Bit7:1; unsigned char OCR1C_Bit8:1, OCR1C_Bit9:1, OCR1C_Bit10:1, OCR1C_Bit11:1, OCR1C_Bit12:1, OCR1C_Bit13:1, OCR1C_Bit14:1, OCR1C_Bit15:1; }; struct { unsigned char OCR1CL; unsigned char OCR1CH; }; struct { unsigned char OCR1CL_Bit0:1, OCR1CL_Bit1:1, OCR1CL_Bit2:1, OCR1CL_Bit3:1, OCR1CL_Bit4:1, OCR1CL_Bit5:1, OCR1CL_Bit6:1, OCR1CL_Bit7:1; unsigned char OCR1CH_Bit0:1, OCR1CH_Bit1:1, OCR1CH_Bit2:1, OCR1CH_Bit3:1, OCR1CH_Bit4:1, OCR1CH_Bit5:1, OCR1CH_Bit6:1, OCR1CH_Bit7:1; }; } @ 0x8C;
__io union { unsigned short OCR1B; struct { unsigned char OCR1B_Bit0:1, OCR1B_Bit1:1, OCR1B_Bit2:1, OCR1B_Bit3:1, OCR1B_Bit4:1, OCR1B_Bit5:1, OCR1B_Bit6:1, OCR1B_Bit7:1; unsigned char OCR1B_Bit8:1, OCR1B_Bit9:1, OCR1B_Bit10:1, OCR1B_Bit11:1, OCR1B_Bit12:1, OCR1B_Bit13:1, OCR1B_Bit14:1, OCR1B_Bit15:1; }; struct { unsigned char OCR1BL; unsigned char OCR1BH; }; struct { unsigned char OCR1BL_Bit0:1, OCR1BL_Bit1:1, OCR1BL_Bit2:1, OCR1BL_Bit3:1, OCR1BL_Bit4:1, OCR1BL_Bit5:1, OCR1BL_Bit6:1, OCR1BL_Bit7:1; unsigned char OCR1BH_Bit0:1, OCR1BH_Bit1:1, OCR1BH_Bit2:1, OCR1BH_Bit3:1, OCR1BH_Bit4:1, OCR1BH_Bit5:1, OCR1BH_Bit6:1, OCR1BH_Bit7:1; }; } @ 0x8A;
__io union { unsigned short OCR1A; struct { unsigned char OCR1A_Bit0:1, OCR1A_Bit1:1, OCR1A_Bit2:1, OCR1A_Bit3:1, OCR1A_Bit4:1, OCR1A_Bit5:1, OCR1A_Bit6:1, OCR1A_Bit7:1; unsigned char OCR1A_Bit8:1, OCR1A_Bit9:1, OCR1A_Bit10:1, OCR1A_Bit11:1, OCR1A_Bit12:1, OCR1A_Bit13:1, OCR1A_Bit14:1, OCR1A_Bit15:1; }; struct { unsigned char OCR1AL; unsigned char OCR1AH; }; struct { unsigned char OCR1AL_Bit0:1, OCR1AL_Bit1:1, OCR1AL_Bit2:1, OCR1AL_Bit3:1, OCR1AL_Bit4:1, OCR1AL_Bit5:1, OCR1AL_Bit6:1, OCR1AL_Bit7:1; unsigned char OCR1AH_Bit0:1, OCR1AH_Bit1:1, OCR1AH_Bit2:1, OCR1AH_Bit3:1, OCR1AH_Bit4:1, OCR1AH_Bit5:1, OCR1AH_Bit6:1, OCR1AH_Bit7:1; }; } @ 0x88;
__io union { unsigned short ICR1; struct { unsigned char ICR1_Bit0:1, ICR1_Bit1:1, ICR1_Bit2:1, ICR1_Bit3:1, ICR1_Bit4:1, ICR1_Bit5:1, ICR1_Bit6:1, ICR1_Bit7:1; unsigned char ICR1_Bit8:1, ICR1_Bit9:1, ICR1_Bit10:1, ICR1_Bit11:1, ICR1_Bit12:1, ICR1_Bit13:1, ICR1_Bit14:1, ICR1_Bit15:1; }; struct { unsigned char ICR1L; unsigned char ICR1H; }; struct { unsigned char ICR1L_Bit0:1, ICR1L_Bit1:1, ICR1L_Bit2:1, ICR1L_Bit3:1, ICR1L_Bit4:1, ICR1L_Bit5:1, ICR1L_Bit6:1, ICR1L_Bit7:1; unsigned char ICR1H_Bit0:1, ICR1H_Bit1:1, ICR1H_Bit2:1, ICR1H_Bit3:1, ICR1H_Bit4:1, ICR1H_Bit5:1, ICR1H_Bit6:1, ICR1H_Bit7:1; }; } @ 0x86;
__io union { unsigned short TCNT1; struct { unsigned char TCNT1_Bit0:1, TCNT1_Bit1:1, TCNT1_Bit2:1, TCNT1_Bit3:1, TCNT1_Bit4:1, TCNT1_Bit5:1, TCNT1_Bit6:1, TCNT1_Bit7:1; unsigned char TCNT1_Bit8:1, TCNT1_Bit9:1, TCNT1_Bit10:1, TCNT1_Bit11:1, TCNT1_Bit12:1, TCNT1_Bit13:1, TCNT1_Bit14:1, TCNT1_Bit15:1; }; struct { unsigned char TCNT1L; unsigned char TCNT1H; }; struct { unsigned char TCNT1L_Bit0:1, TCNT1L_Bit1:1, TCNT1L_Bit2:1, TCNT1L_Bit3:1, TCNT1L_Bit4:1, TCNT1L_Bit5:1, TCNT1L_Bit6:1, TCNT1L_Bit7:1; unsigned char TCNT1H_Bit0:1, TCNT1H_Bit1:1, TCNT1H_Bit2:1, TCNT1H_Bit3:1, TCNT1H_Bit4:1, TCNT1H_Bit5:1, TCNT1H_Bit6:1, TCNT1H_Bit7:1; }; } @ 0x84;
__io union { unsigned char TCCR1C; struct { unsigned char TCCR1C_Bit0:1, TCCR1C_Bit1:1, TCCR1C_Bit2:1, TCCR1C_Bit3:1, TCCR1C_Bit4:1, TCCR1C_Bit5:1, TCCR1C_Bit6:1, TCCR1C_Bit7:1; }; struct { unsigned char TCCR1C_Dummy0:1, TCCR1C_Dummy1:1, TCCR1C_Dummy2:1, TCCR1C_Dummy3:1, TCCR1C_Dummy4:1, TCCR1C_FOC1C:1, TCCR1C_FOC1B:1, TCCR1C_FOC1A:1; }; } @ 0x82;
__io union { unsigned char TCCR1B; struct { unsigned char TCCR1B_Bit0:1, TCCR1B_Bit1:1, TCCR1B_Bit2:1, TCCR1B_Bit3:1, TCCR1B_Bit4:1, TCCR1B_Bit5:1, TCCR1B_Bit6:1, TCCR1B_Bit7:1; }; struct { unsigned char TCCR1B_CS10:1, TCCR1B_CS11:1, TCCR1B_CS12:1, TCCR1B_WGM12:1, TCCR1B_WGM13:1, TCCR1B_Dummy5:1, TCCR1B_ICES1:1, TCCR1B_ICNC1:1; }; } @ 0x81;
__io union { unsigned char TCCR1A; struct { unsigned char TCCR1A_Bit0:1, TCCR1A_Bit1:1, TCCR1A_Bit2:1, TCCR1A_Bit3:1, TCCR1A_Bit4:1, TCCR1A_Bit5:1, TCCR1A_Bit6:1, TCCR1A_Bit7:1; }; struct { unsigned char TCCR1A_WGM10:1, TCCR1A_WGM11:1, TCCR1A_COM1C0:1, TCCR1A_COM1C1:1, TCCR1A_COM1B0:1, TCCR1A_COM1B1:1, TCCR1A_COM1A0:1, TCCR1A_COM1A1:1; }; } @ 0x80;
__io union { unsigned char DIDR1; struct { unsigned char DIDR1_Bit0:1, DIDR1_Bit1:1, DIDR1_Bit2:1, DIDR1_Bit3:1, DIDR1_Bit4:1, DIDR1_Bit5:1, DIDR1_Bit6:1, DIDR1_Bit7:1; }; struct { unsigned char DIDR1_AIN0D:1, DIDR1_AIN1D:1, DIDR1_Dummy2:1, DIDR1_Dummy3:1, DIDR1_Dummy4:1, DIDR1_Dummy5:1, DIDR1_Dummy6:1, DIDR1_Dummy7:1; }; } @ 0x7F;
__io union { unsigned char DIDR0; struct { unsigned char DIDR0_Bit0:1, DIDR0_Bit1:1, DIDR0_Bit2:1, DIDR0_Bit3:1, DIDR0_Bit4:1, DIDR0_Bit5:1, DIDR0_Bit6:1, DIDR0_Bit7:1; }; struct { unsigned char DIDR0_ADC0D:1, DIDR0_ADC1D:1, DIDR0_ADC2D:1, DIDR0_ADC3D:1, DIDR0_ADC4D:1, DIDR0_ADC5D:1, DIDR0_ADC6D:1, DIDR0_ADC7D:1; }; } @ 0x7E;
__io union { unsigned char DIDR2; struct { unsigned char DIDR2_Bit0:1, DIDR2_Bit1:1, DIDR2_Bit2:1, DIDR2_Bit3:1, DIDR2_Bit4:1, DIDR2_Bit5:1, DIDR2_Bit6:1, DIDR2_Bit7:1; }; struct { unsigned char DIDR2_ADC8D:1, DIDR2_ADC9D:1, DIDR2_ADC10D:1, DIDR2_ADC11D:1, DIDR2_ADC12D:1, DIDR2_ADC13D:1, DIDR2_ADC14D:1, DIDR2_ADC15D:1; }; } @ 0x7D;
__io union { unsigned char ADMUX; struct { unsigned char ADMUX_Bit0:1, ADMUX_Bit1:1, ADMUX_Bit2:1, ADMUX_Bit3:1, ADMUX_Bit4:1, ADMUX_Bit5:1, ADMUX_Bit6:1, ADMUX_Bit7:1; }; struct { unsigned char ADMUX_MUX0:1, ADMUX_MUX1:1, ADMUX_MUX2:1, ADMUX_MUX3:1, ADMUX_MUX4:1, ADMUX_ADLAR:1, ADMUX_REFS0:1, ADMUX_REFS1:1; }; } @ 0x7C;
__io union { unsigned char ADCSRB; struct { unsigned char ADCSRB_Bit0:1, ADCSRB_Bit1:1, ADCSRB_Bit2:1, ADCSRB_Bit3:1, ADCSRB_Bit4:1, ADCSRB_Bit5:1, ADCSRB_Bit6:1, ADCSRB_Bit7:1; }; struct { unsigned char ADCSRB_ADTS0:1, ADCSRB_ADTS1:1, ADCSRB_ADTS2:1, ADCSRB_MUX5:1, ADCSRB_Dummy4:1, ADCSRB_Dummy5:1, ADCSRB_ACME:1, ADCSRB_Dummy7:1; }; } @ 0x7B;
__io union { unsigned char ADCSRA; struct { unsigned char ADCSRA_Bit0:1, ADCSRA_Bit1:1, ADCSRA_Bit2:1, ADCSRA_Bit3:1, ADCSRA_Bit4:1, ADCSRA_Bit5:1, ADCSRA_Bit6:1, ADCSRA_Bit7:1; }; struct { unsigned char ADCSRA_ADPS0:1, ADCSRA_ADPS1:1, ADCSRA_ADPS2:1, ADCSRA_ADIE:1, ADCSRA_ADIF:1, ADCSRA_ADATE:1, ADCSRA_ADSC:1, ADCSRA_ADEN:1; }; } @ 0x7A;
__io union { unsigned short ADC; struct { unsigned char ADC_Bit0:1, ADC_Bit1:1, ADC_Bit2:1, ADC_Bit3:1, ADC_Bit4:1, ADC_Bit5:1, ADC_Bit6:1, ADC_Bit7:1; unsigned char ADC_Bit8:1, ADC_Bit9:1, ADC_Bit10:1, ADC_Bit11:1, ADC_Bit12:1, ADC_Bit13:1, ADC_Bit14:1, ADC_Bit15:1; }; struct { unsigned char ADCL; unsigned char ADCH; }; struct { unsigned char ADCL_Bit0:1, ADCL_Bit1:1, ADCL_Bit2:1, ADCL_Bit3:1, ADCL_Bit4:1, ADCL_Bit5:1, ADCL_Bit6:1, ADCL_Bit7:1; unsigned char ADCH_Bit0:1, ADCH_Bit1:1, ADCH_Bit2:1, ADCH_Bit3:1, ADCH_Bit4:1, ADCH_Bit5:1, ADCH_Bit6:1, ADCH_Bit7:1; }; } @ 0x78;
__io union { unsigned char XMCRB; struct { unsigned char XMCRB_Bit0:1, XMCRB_Bit1:1, XMCRB_Bit2:1, XMCRB_Bit3:1, XMCRB_Bit4:1, XMCRB_Bit5:1, XMCRB_Bit6:1, XMCRB_Bit7:1; }; struct { unsigned char XMCRB_XMM0:1, XMCRB_XMM1:1, XMCRB_XMM2:1, XMCRB_Dummy3:1, XMCRB_Dummy4:1, XMCRB_Dummy5:1, XMCRB_Dummy6:1, XMCRB_XMBK:1; }; } @ 0x75;
__io union { unsigned char XMCRA; struct { unsigned char XMCRA_Bit0:1, XMCRA_Bit1:1, XMCRA_Bit2:1, XMCRA_Bit3:1, XMCRA_Bit4:1, XMCRA_Bit5:1, XMCRA_Bit6:1, XMCRA_Bit7:1; }; struct { unsigned char XMCRA_SRW00:1, XMCRA_SRW01:1, XMCRA_SRW10:1, XMCRA_SRW11:1, XMCRA_SRL0:1, XMCRA_SRL1:1, XMCRA_SRL2:1, XMCRA_SRE:1; }; } @ 0x74;
__io union { unsigned char TIMSK5; struct { unsigned char TIMSK5_Bit0:1, TIMSK5_Bit1:1, TIMSK5_Bit2:1, TIMSK5_Bit3:1, TIMSK5_Bit4:1, TIMSK5_Bit5:1, TIMSK5_Bit6:1, TIMSK5_Bit7:1; }; struct { unsigned char TIMSK5_TOIE5:1, TIMSK5_OCIE5A:1, TIMSK5_OCIE5B:1, TIMSK5_OCIE5C:1, TIMSK5_Dummy4:1, TIMSK5_ICIE5:1, TIMSK5_Dummy6:1, TIMSK5_Dummy7:1; }; } @ 0x73;
__io union { unsigned char TIMSK4; struct { unsigned char TIMSK4_Bit0:1, TIMSK4_Bit1:1, TIMSK4_Bit2:1, TIMSK4_Bit3:1, TIMSK4_Bit4:1, TIMSK4_Bit5:1, TIMSK4_Bit6:1, TIMSK4_Bit7:1; }; struct { unsigned char TIMSK4_TOIE4:1, TIMSK4_OCIE4A:1, TIMSK4_OCIE4B:1, TIMSK4_OCIE4C:1, TIMSK4_Dummy4:1, TIMSK4_ICIE4:1, TIMSK4_Dummy6:1, TIMSK4_Dummy7:1; }; } @ 0x72;
__io union { unsigned char TIMSK3; struct { unsigned char TIMSK3_Bit0:1, TIMSK3_Bit1:1, TIMSK3_Bit2:1, TIMSK3_Bit3:1, TIMSK3_Bit4:1, TIMSK3_Bit5:1, TIMSK3_Bit6:1, TIMSK3_Bit7:1; }; struct { unsigned char TIMSK3_TOIE3:1, TIMSK3_OCIE3A:1, TIMSK3_OCIE3B:1, TIMSK3_OCIE3C:1, TIMSK3_Dummy4:1, TIMSK3_ICIE3:1, TIMSK3_Dummy6:1, TIMSK3_Dummy7:1; }; } @ 0x71;
__io union { unsigned char TIMSK2; struct { unsigned char TIMSK2_Bit0:1, TIMSK2_Bit1:1, TIMSK2_Bit2:1, TIMSK2_Bit3:1, TIMSK2_Bit4:1, TIMSK2_Bit5:1, TIMSK2_Bit6:1, TIMSK2_Bit7:1; }; struct { unsigned char TIMSK2_TOIE2:1, TIMSK2_OCIE2A:1, TIMSK2_OCIE2B:1, TIMSK2_Dummy3:1, TIMSK2_Dummy4:1, TIMSK2_Dummy5:1, TIMSK2_Dummy6:1, TIMSK2_Dummy7:1; }; } @ 0x70;
__io union { unsigned char TIMSK1; struct { unsigned char TIMSK1_Bit0:1, TIMSK1_Bit1:1, TIMSK1_Bit2:1, TIMSK1_Bit3:1, TIMSK1_Bit4:1, TIMSK1_Bit5:1, TIMSK1_Bit6:1, TIMSK1_Bit7:1; }; struct { unsigned char TIMSK1_TOIE1:1, TIMSK1_OCIE1A:1, TIMSK1_OCIE1B:1, TIMSK1_OCIE1C:1, TIMSK1_Dummy4:1, TIMSK1_ICIE1:1, TIMSK1_Dummy6:1, TIMSK1_Dummy7:1; }; } @ 0x6F;
__io union { unsigned char TIMSK0; struct { unsigned char TIMSK0_Bit0:1, TIMSK0_Bit1:1, TIMSK0_Bit2:1, TIMSK0_Bit3:1, TIMSK0_Bit4:1, TIMSK0_Bit5:1, TIMSK0_Bit6:1, TIMSK0_Bit7:1; }; struct { unsigned char TIMSK0_TOIE0:1, TIMSK0_OCIE0A:1, TIMSK0_OCIE0B:1, TIMSK0_Dummy3:1, TIMSK0_Dummy4:1, TIMSK0_Dummy5:1, TIMSK0_Dummy6:1, TIMSK0_Dummy7:1; }; } @ 0x6E;
__io union { unsigned char PCMSK2; struct { unsigned char PCMSK2_Bit0:1, PCMSK2_Bit1:1, PCMSK2_Bit2:1, PCMSK2_Bit3:1, PCMSK2_Bit4:1, PCMSK2_Bit5:1, PCMSK2_Bit6:1, PCMSK2_Bit7:1; }; struct { unsigned char PCMSK2_PCINT16:1, PCMSK2_PCINT17:1, PCMSK2_PCINT18:1, PCMSK2_PCINT19:1, PCMSK2_PCINT20:1, PCMSK2_PCINT21:1, PCMSK2_PCINT22:1, PCMSK2_PCINT23:1; }; } @ 0x6D;
__io union { unsigned char PCMSK1; struct { unsigned char PCMSK1_Bit0:1, PCMSK1_Bit1:1, PCMSK1_Bit2:1, PCMSK1_Bit3:1, PCMSK1_Bit4:1, PCMSK1_Bit5:1, PCMSK1_Bit6:1, PCMSK1_Bit7:1; }; struct { unsigned char PCMSK1_PCINT8:1, PCMSK1_PCINT9:1, PCMSK1_PCINT10:1, PCMSK1_PCINT11:1, PCMSK1_PCINT12:1, PCMSK1_PCINT13:1, PCMSK1_PCINT14:1, PCMSK1_PCINT15:1; }; } @ 0x6C;
__io union { unsigned char PCMSK0; struct { unsigned char PCMSK0_Bit0:1, PCMSK0_Bit1:1, PCMSK0_Bit2:1, PCMSK0_Bit3:1, PCMSK0_Bit4:1, PCMSK0_Bit5:1, PCMSK0_Bit6:1, PCMSK0_Bit7:1; }; struct { unsigned char PCMSK0_PCINT0:1, PCMSK0_PCINT1:1, PCMSK0_PCINT2:1, PCMSK0_PCINT3:1, PCMSK0_PCINT4:1, PCMSK0_PCINT5:1, PCMSK0_PCINT6:1, PCMSK0_PCINT7:1; }; } @ 0x6B;
__io union { unsigned char EICRB; struct { unsigned char EICRB_Bit0:1, EICRB_Bit1:1, EICRB_Bit2:1, EICRB_Bit3:1, EICRB_Bit4:1, EICRB_Bit5:1, EICRB_Bit6:1, EICRB_Bit7:1; }; struct { unsigned char EICRB_ISC40:1, EICRB_ISC41:1, EICRB_ISC50:1, EICRB_ISC51:1, EICRB_ISC60:1, EICRB_ISC61:1, EICRB_ISC70:1, EICRB_ISC71:1; }; } @ 0x6A;
__io union { unsigned char EICRA; struct { unsigned char EICRA_Bit0:1, EICRA_Bit1:1, EICRA_Bit2:1, EICRA_Bit3:1, EICRA_Bit4:1, EICRA_Bit5:1, EICRA_Bit6:1, EICRA_Bit7:1; }; struct { unsigned char EICRA_ISC00:1, EICRA_ISC01:1, EICRA_ISC10:1, EICRA_ISC11:1, EICRA_ISC20:1, EICRA_ISC21:1, EICRA_ISC30:1, EICRA_ISC31:1; }; } @ 0x69;
__io union { unsigned char PCICR; struct { unsigned char PCICR_Bit0:1, PCICR_Bit1:1, PCICR_Bit2:1, PCICR_Bit3:1, PCICR_Bit4:1, PCICR_Bit5:1, PCICR_Bit6:1, PCICR_Bit7:1; }; struct { unsigned char PCICR_PCIE0:1, PCICR_PCIE1:1, PCICR_PCIE2:1, PCICR_Dummy3:1, PCICR_Dummy4:1, PCICR_Dummy5:1, PCICR_Dummy6:1, PCICR_Dummy7:1; }; } @ 0x68;
__io union { unsigned char OSCCAL; struct { unsigned char OSCCAL_Bit0:1, OSCCAL_Bit1:1, OSCCAL_Bit2:1, OSCCAL_Bit3:1, OSCCAL_Bit4:1, OSCCAL_Bit5:1, OSCCAL_Bit6:1, OSCCAL_Bit7:1; }; } @ 0x66;
__io union { unsigned char PRR1; struct { unsigned char PRR1_Bit0:1, PRR1_Bit1:1, PRR1_Bit2:1, PRR1_Bit3:1, PRR1_Bit4:1, PRR1_Bit5:1, PRR1_Bit6:1, PRR1_Bit7:1; }; struct { unsigned char PRR1_PRUSART1:1, PRR1_PRUSART2:1, PRR1_PRUSART3:1, PRR1_PRTIM3:1, PRR1_PRTIM4:1, PRR1_PRTIM5:1, PRR1_Dummy6:1, PRR1_Dummy7:1; }; } @ 0x65;
__io union { unsigned char PRR0; struct { unsigned char PRR0_Bit0:1, PRR0_Bit1:1, PRR0_Bit2:1, PRR0_Bit3:1, PRR0_Bit4:1, PRR0_Bit5:1, PRR0_Bit6:1, PRR0_Bit7:1; }; struct { unsigned char PRR0_PRADC:1, PRR0_PRUSART0:1, PRR0_PRSPI:1, PRR0_PRTIM1:1, PRR0_Dummy4:1, PRR0_PRTIM0:1, PRR0_PRTIM2:1, PRR0_PRTWI:1; }; } @ 0x64;
__io union { unsigned char CLKPR; struct { unsigned char CLKPR_Bit0:1, CLKPR_Bit1:1, CLKPR_Bit2:1, CLKPR_Bit3:1, CLKPR_Bit4:1, CLKPR_Bit5:1, CLKPR_Bit6:1, CLKPR_Bit7:1; }; struct { unsigned char CLKPR_CLKPS0:1, CLKPR_CLKPS1:1, CLKPR_CLKPS2:1, CLKPR_CLKPS3:1, CLKPR_Dummy4:1, CLKPR_Dummy5:1, CLKPR_Dummy6:1, CLKPR_CLKPCE:1; }; } @ 0x61;
__io union { unsigned char WDTCSR; struct { unsigned char WDTCSR_Bit0:1, WDTCSR_Bit1:1, WDTCSR_Bit2:1, WDTCSR_Bit3:1, WDTCSR_Bit4:1, WDTCSR_Bit5:1, WDTCSR_Bit6:1, WDTCSR_Bit7:1; }; struct { unsigned char WDTCSR_WDP0:1, WDTCSR_WDP1:1, WDTCSR_WDP2:1, WDTCSR_WDE:1, WDTCSR_WDCE:1, WDTCSR_WDP3:1, WDTCSR_WDIE:1, WDTCSR_WDIF:1; }; } @ 0x60;

__io union { unsigned char SREG; struct { unsigned char SREG_Bit0:1, SREG_Bit1:1, SREG_Bit2:1, SREG_Bit3:1, SREG_Bit4:1, SREG_Bit5:1, SREG_Bit6:1, SREG_Bit7:1; }; struct { unsigned char SREG_C:1, SREG_Z:1, SREG_N:1, SREG_V:1, SREG_S:1, SREG_H:1, SREG_T:1, SREG_I:1; }; } @ 0x3F;
__io union { unsigned short SP; struct { unsigned char SP_Bit0:1, SP_Bit1:1, SP_Bit2:1, SP_Bit3:1, SP_Bit4:1, SP_Bit5:1, SP_Bit6:1, SP_Bit7:1; unsigned char SP_Bit8:1, SP_Bit9:1, SP_Bit10:1, SP_Bit11:1, SP_Bit12:1, SP_Bit13:1, SP_Bit14:1, SP_Bit15:1; }; struct { unsigned char SP_SP0:1, SP_SP1:1, SP_SP2:1, SP_SP3:1, SP_SP4:1, SP_SP5:1, SP_SP6:1, SP_SP7:1; unsigned char SP_SP8:1, SP_SP9:1, SP_SP10:1, SP_SP11:1, SP_SP12:1, SP_SP13:1, SP_SP14:1, SP_SP15:1; }; struct { unsigned char SPL; unsigned char SPH; }; struct { unsigned char SPL_Bit0:1, SPL_Bit1:1, SPL_Bit2:1, SPL_Bit3:1, SPL_Bit4:1, SPL_Bit5:1, SPL_Bit6:1, SPL_Bit7:1; unsigned char SPH_Bit0:1, SPH_Bit1:1, SPH_Bit2:1, SPH_Bit3:1, SPH_Bit4:1, SPH_Bit5:1, SPH_Bit6:1, SPH_Bit7:1; }; struct { unsigned char SPL_SP0:1, SPL_SP1:1, SPL_SP2:1, SPL_SP3:1, SPL_SP4:1, SPL_SP5:1, SPL_SP6:1, SPL_SP7:1; unsigned char SPH_SP8:1, SPH_SP9:1, SPH_SP10:1, SPH_SP11:1, SPH_SP12:1, SPH_SP13:1, SPH_SP14:1, SPH_SP15:1; }; } @ 0x3D;
__io union { unsigned char EIND; struct { unsigned char EIND_Bit0:1, EIND_Bit1:1, EIND_Bit2:1, EIND_Bit3:1, EIND_Bit4:1, EIND_Bit5:1, EIND_Bit6:1, EIND_Bit7:1; }; struct { unsigned char EIND_EIND0:1, EIND_Dummy1:1, EIND_Dummy2:1, EIND_Dummy3:1, EIND_Dummy4:1, EIND_Dummy5:1, EIND_Dummy6:1, EIND_Dummy7:1; }; } @ 0x3C;
__io union { unsigned char RAMPZ; struct { unsigned char RAMPZ_Bit0:1, RAMPZ_Bit1:1, RAMPZ_Bit2:1, RAMPZ_Bit3:1, RAMPZ_Bit4:1, RAMPZ_Bit5:1, RAMPZ_Bit6:1, RAMPZ_Bit7:1; }; struct { unsigned char RAMPZ_RAMPZ0:1, RAMPZ_RAMPZ1:1, RAMPZ_Dummy2:1, RAMPZ_Dummy3:1, RAMPZ_Dummy4:1, RAMPZ_Dummy5:1, RAMPZ_Dummy6:1, RAMPZ_Dummy7:1; }; } @ 0x3B;
__io union { unsigned char SPMCSR; struct { unsigned char SPMCSR_Bit0:1, SPMCSR_Bit1:1, SPMCSR_Bit2:1, SPMCSR_Bit3:1, SPMCSR_Bit4:1, SPMCSR_Bit5:1, SPMCSR_Bit6:1, SPMCSR_Bit7:1; }; struct { unsigned char SPMCSR_SPMEN:1, SPMCSR_PGERS:1, SPMCSR_PGWRT:1, SPMCSR_BLBSET:1, SPMCSR_RWWSRE:1, SPMCSR_SIGRD:1, SPMCSR_RWWSB:1, SPMCSR_SPMIE:1; }; } @ 0x37;
__io union { unsigned char MCUCR; struct { unsigned char MCUCR_Bit0:1, MCUCR_Bit1:1, MCUCR_Bit2:1, MCUCR_Bit3:1, MCUCR_Bit4:1, MCUCR_Bit5:1, MCUCR_Bit6:1, MCUCR_Bit7:1; }; struct { unsigned char MCUCR_IVCE:1, MCUCR_IVSEL:1, MCUCR_Dummy2:1, MCUCR_Dummy3:1, MCUCR_PUD:1, MCUCR_Dummy5:1, MCUCR_Dummy6:1, MCUCR_JTD:1; }; } @ 0x35;
__io union { unsigned char MCUSR; struct { unsigned char MCUSR_Bit0:1, MCUSR_Bit1:1, MCUSR_Bit2:1, MCUSR_Bit3:1, MCUSR_Bit4:1, MCUSR_Bit5:1, MCUSR_Bit6:1, MCUSR_Bit7:1; }; struct { unsigned char MCUSR_PORF:1, MCUSR_EXTRF:1, MCUSR_BORF:1, MCUSR_WDRF:1, MCUSR_JTRF:1, MCUSR_Dummy5:1, MCUSR_Dummy6:1, MCUSR_Dummy7:1; }; } @ 0x34;
__io union { unsigned char SMCR; struct { unsigned char SMCR_Bit0:1, SMCR_Bit1:1, SMCR_Bit2:1, SMCR_Bit3:1, SMCR_Bit4:1, SMCR_Bit5:1, SMCR_Bit6:1, SMCR_Bit7:1; }; struct { unsigned char SMCR_SE:1, SMCR_SM0:1, SMCR_SM1:1, SMCR_SM2:1, SMCR_Dummy4:1, SMCR_Dummy5:1, SMCR_Dummy6:1, SMCR_Dummy7:1; }; } @ 0x33;
__io union { unsigned char OCDR; unsigned char MONDR; struct { unsigned char OCDR_Bit0:1, OCDR_Bit1:1, OCDR_Bit2:1, OCDR_Bit3:1, OCDR_Bit4:1, OCDR_Bit5:1, OCDR_Bit6:1, OCDR_Bit7:1; }; struct { unsigned char MONDR_Bit0:1, MONDR_Bit1:1, MONDR_Bit2:1, MONDR_Bit3:1, MONDR_Bit4:1, MONDR_Bit5:1, MONDR_Bit6:1, MONDR_Bit7:1; }; struct { unsigned char OCDR_OCDR0:1, OCDR_OCDR1:1, OCDR_OCDR2:1, OCDR_OCDR3:1, OCDR_OCDR4:1, OCDR_OCDR5:1, OCDR_OCDR6:1, OCDR_OCDR7:1; }; struct { unsigned char MONDR_OCDR0:1, MONDR_OCDR1:1, MONDR_OCDR2:1, MONDR_OCDR3:1, MONDR_OCDR4:1, MONDR_OCDR5:1, MONDR_OCDR6:1, MONDR_OCDR7:1; }; } @ 0x31;
__io union { unsigned char ACSR; struct { unsigned char ACSR_Bit0:1, ACSR_Bit1:1, ACSR_Bit2:1, ACSR_Bit3:1, ACSR_Bit4:1, ACSR_Bit5:1, ACSR_Bit6:1, ACSR_Bit7:1; }; struct { unsigned char ACSR_ACIS0:1, ACSR_ACIS1:1, ACSR_ACIC:1, ACSR_ACIE:1, ACSR_ACI:1, ACSR_ACO:1, ACSR_ACBG:1, ACSR_ACD:1; }; } @ 0x30;
__io union { unsigned char SPDR; struct { unsigned char SPDR_Bit0:1, SPDR_Bit1:1, SPDR_Bit2:1, SPDR_Bit3:1, SPDR_Bit4:1, SPDR_Bit5:1, SPDR_Bit6:1, SPDR_Bit7:1; }; } @ 0x2E;
__io union { unsigned char SPSR; struct { unsigned char SPSR_Bit0:1, SPSR_Bit1:1, SPSR_Bit2:1, SPSR_Bit3:1, SPSR_Bit4:1, SPSR_Bit5:1, SPSR_Bit6:1, SPSR_Bit7:1; }; struct { unsigned char SPSR_SPI2X:1, SPSR_Dummy1:1, SPSR_Dummy2:1, SPSR_Dummy3:1, SPSR_Dummy4:1, SPSR_Dummy5:1, SPSR_WCOL:1, SPSR_SPIF:1; }; } @ 0x2D;
__io union { unsigned char SPCR; struct { unsigned char SPCR_Bit0:1, SPCR_Bit1:1, SPCR_Bit2:1, SPCR_Bit3:1, SPCR_Bit4:1, SPCR_Bit5:1, SPCR_Bit6:1, SPCR_Bit7:1; }; struct { unsigned char SPCR_SPR0:1, SPCR_SPR1:1, SPCR_CPHA:1, SPCR_CPOL:1, SPCR_MSTR:1, SPCR_DORD:1, SPCR_SPE:1, SPCR_SPIE:1; }; } @ 0x2C;
__io union { unsigned char GPIOR2; struct { unsigned char GPIOR2_Bit0:1, GPIOR2_Bit1:1, GPIOR2_Bit2:1, GPIOR2_Bit3:1, GPIOR2_Bit4:1, GPIOR2_Bit5:1, GPIOR2_Bit6:1, GPIOR2_Bit7:1; }; } @ 0x2B;
__io union { unsigned char GPIOR1; struct { unsigned char GPIOR1_Bit0:1, GPIOR1_Bit1:1, GPIOR1_Bit2:1, GPIOR1_Bit3:1, GPIOR1_Bit4:1, GPIOR1_Bit5:1, GPIOR1_Bit6:1, GPIOR1_Bit7:1; }; } @ 0x2A;
__io union { unsigned char OCR0B; struct { unsigned char OCR0B_Bit0:1, OCR0B_Bit1:1, OCR0B_Bit2:1, OCR0B_Bit3:1, OCR0B_Bit4:1, OCR0B_Bit5:1, OCR0B_Bit6:1, OCR0B_Bit7:1; }; } @ 0x28;
__io union { unsigned char OCR0A; struct { unsigned char OCR0A_Bit0:1, OCR0A_Bit1:1, OCR0A_Bit2:1, OCR0A_Bit3:1, OCR0A_Bit4:1, OCR0A_Bit5:1, OCR0A_Bit6:1, OCR0A_Bit7:1; }; } @ 0x27;
__io union { unsigned char TCNT0; struct { unsigned char TCNT0_Bit0:1, TCNT0_Bit1:1, TCNT0_Bit2:1, TCNT0_Bit3:1, TCNT0_Bit4:1, TCNT0_Bit5:1, TCNT0_Bit6:1, TCNT0_Bit7:1; }; } @ 0x26;
__io union { unsigned char TCCR0B; struct { unsigned char TCCR0B_Bit0:1, TCCR0B_Bit1:1, TCCR0B_Bit2:1, TCCR0B_Bit3:1, TCCR0B_Bit4:1, TCCR0B_Bit5:1, TCCR0B_Bit6:1, TCCR0B_Bit7:1; }; struct { unsigned char TCCR0B_CS00:1, TCCR0B_CS01:1, TCCR0B_CS02:1, TCCR0B_WGM02:1, TCCR0B_Dummy4:1, TCCR0B_Dummy5:1, TCCR0B_FOC0B:1, TCCR0B_FOC0A:1; }; } @ 0x25;
__io union { unsigned char TCCR0A; struct { unsigned char TCCR0A_Bit0:1, TCCR0A_Bit1:1, TCCR0A_Bit2:1, TCCR0A_Bit3:1, TCCR0A_Bit4:1, TCCR0A_Bit5:1, TCCR0A_Bit6:1, TCCR0A_Bit7:1; }; struct { unsigned char TCCR0A_WGM00:1, TCCR0A_WGM01:1, TCCR0A_Dummy2:1, TCCR0A_Dummy3:1, TCCR0A_COM0B0:1, TCCR0A_COM0B1:1, TCCR0A_COM0A0:1, TCCR0A_COM0A1:1; }; } @ 0x24;
__io union { unsigned char GTCCR; struct { unsigned char GTCCR_Bit0:1, GTCCR_Bit1:1, GTCCR_Bit2:1, GTCCR_Bit3:1, GTCCR_Bit4:1, GTCCR_Bit5:1, GTCCR_Bit6:1, GTCCR_Bit7:1; }; struct { unsigned char GTCCR_PSRSYNC:1, GTCCR_PSRASY:1, GTCCR_Dummy2:1, GTCCR_Dummy3:1, GTCCR_Dummy4:1, GTCCR_Dummy5:1, GTCCR_Dummy6:1, GTCCR_TSM:1; }; } @ 0x23;
__io union { unsigned short EEAR; struct { unsigned char EEAR_Bit0:1, EEAR_Bit1:1, EEAR_Bit2:1, EEAR_Bit3:1, EEAR_Bit4:1, EEAR_Bit5:1, EEAR_Bit6:1, EEAR_Bit7:1; unsigned char EEAR_Bit8:1, EEAR_Bit9:1, EEAR_Bit10:1, EEAR_Bit11:1, EEAR_Bit12:1, EEAR_Bit13:1, EEAR_Bit14:1, EEAR_Bit15:1; }; struct { unsigned char EEARL; unsigned char EEARH; }; struct { unsigned char EEARL_Bit0:1, EEARL_Bit1:1, EEARL_Bit2:1, EEARL_Bit3:1, EEARL_Bit4:1, EEARL_Bit5:1, EEARL_Bit6:1, EEARL_Bit7:1; unsigned char EEARH_Bit0:1, EEARH_Bit1:1, EEARH_Bit2:1, EEARH_Bit3:1, EEARH_Bit4:1, EEARH_Bit5:1, EEARH_Bit6:1, EEARH_Bit7:1; }; } @ 0x21;
__io union { unsigned char EEDR; struct { unsigned char EEDR_Bit0:1, EEDR_Bit1:1, EEDR_Bit2:1, EEDR_Bit3:1, EEDR_Bit4:1, EEDR_Bit5:1, EEDR_Bit6:1, EEDR_Bit7:1; }; } @ 0x20;
__io union { unsigned char EECR; struct { unsigned char EECR_Bit0:1, EECR_Bit1:1, EECR_Bit2:1, EECR_Bit3:1, EECR_Bit4:1, EECR_Bit5:1, EECR_Bit6:1, EECR_Bit7:1; }; struct { unsigned char EECR_EERE:1, EECR_EEPE:1, EECR_EEMPE:1, EECR_EERIE:1, EECR_EEPM0:1, EECR_EEPM1:1, EECR_Dummy6:1, EECR_Dummy7:1; }; } @ 0x1F;
__io union { unsigned char GPIOR0; struct { unsigned char GPIOR0_Bit0:1, GPIOR0_Bit1:1, GPIOR0_Bit2:1, GPIOR0_Bit3:1, GPIOR0_Bit4:1, GPIOR0_Bit5:1, GPIOR0_Bit6:1, GPIOR0_Bit7:1; }; } @ 0x1E;
__io union { unsigned char EIMSK; struct { unsigned char EIMSK_Bit0:1, EIMSK_Bit1:1, EIMSK_Bit2:1, EIMSK_Bit3:1, EIMSK_Bit4:1, EIMSK_Bit5:1, EIMSK_Bit6:1, EIMSK_Bit7:1; }; struct { unsigned char EIMSK_INT0:1, EIMSK_INT1:1, EIMSK_INT2:1, EIMSK_INT3:1, EIMSK_INT4:1, EIMSK_INT5:1, EIMSK_INT6:1, EIMSK_INT7:1; }; } @ 0x1D;
__io union { unsigned char EIFR; struct { unsigned char EIFR_Bit0:1, EIFR_Bit1:1, EIFR_Bit2:1, EIFR_Bit3:1, EIFR_Bit4:1, EIFR_Bit5:1, EIFR_Bit6:1, EIFR_Bit7:1; }; struct { unsigned char EIFR_INTF0:1, EIFR_INTF1:1, EIFR_INTF2:1, EIFR_INTF3:1, EIFR_INTF4:1, EIFR_INTF5:1, EIFR_INTF6:1, EIFR_INTF7:1; }; } @ 0x1C;
__io union { unsigned char PCIFR; struct { unsigned char PCIFR_Bit0:1, PCIFR_Bit1:1, PCIFR_Bit2:1, PCIFR_Bit3:1, PCIFR_Bit4:1, PCIFR_Bit5:1, PCIFR_Bit6:1, PCIFR_Bit7:1; }; struct { unsigned char PCIFR_PCIF0:1, PCIFR_PCIF1:1, PCIFR_PCIF2:1, PCIFR_Dummy3:1, PCIFR_Dummy4:1, PCIFR_Dummy5:1, PCIFR_Dummy6:1, PCIFR_Dummy7:1; }; } @ 0x1B;
__io union { unsigned char TIFR5; struct { unsigned char TIFR5_Bit0:1, TIFR5_Bit1:1, TIFR5_Bit2:1, TIFR5_Bit3:1, TIFR5_Bit4:1, TIFR5_Bit5:1, TIFR5_Bit6:1, TIFR5_Bit7:1; }; struct { unsigned char TIFR5_TOV5:1, TIFR5_OCF5A:1, TIFR5_OCF5B:1, TIFR5_OCF5C:1, TIFR5_Dummy4:1, TIFR5_ICF5:1, TIFR5_Dummy6:1, TIFR5_Dummy7:1; }; } @ 0x1A;
__io union { unsigned char TIFR4; struct { unsigned char TIFR4_Bit0:1, TIFR4_Bit1:1, TIFR4_Bit2:1, TIFR4_Bit3:1, TIFR4_Bit4:1, TIFR4_Bit5:1, TIFR4_Bit6:1, TIFR4_Bit7:1; }; struct { unsigned char TIFR4_TOV4:1, TIFR4_OCF4A:1, TIFR4_OCF4B:1, TIFR4_OCF4C:1, TIFR4_Dummy4:1, TIFR4_ICF4:1, TIFR4_Dummy6:1, TIFR4_Dummy7:1; }; } @ 0x19;
__io union { unsigned char TIFR3; struct { unsigned char TIFR3_Bit0:1, TIFR3_Bit1:1, TIFR3_Bit2:1, TIFR3_Bit3:1, TIFR3_Bit4:1, TIFR3_Bit5:1, TIFR3_Bit6:1, TIFR3_Bit7:1; }; struct { unsigned char TIFR3_TOV3:1, TIFR3_OCF3A:1, TIFR3_OCF3B:1, TIFR3_OCF3C:1, TIFR3_Dummy4:1, TIFR3_ICF3:1, TIFR3_Dummy6:1, TIFR3_Dummy7:1; }; } @ 0x18;
__io union { unsigned char TIFR2; struct { unsigned char TIFR2_Bit0:1, TIFR2_Bit1:1, TIFR2_Bit2:1, TIFR2_Bit3:1, TIFR2_Bit4:1, TIFR2_Bit5:1, TIFR2_Bit6:1, TIFR2_Bit7:1; }; struct { unsigned char TIFR2_TOV2:1, TIFR2_OCF2A:1, TIFR2_OCF2B:1, TIFR2_Dummy3:1, TIFR2_Dummy4:1, TIFR2_Dummy5:1, TIFR2_Dummy6:1, TIFR2_Dummy7:1; }; } @ 0x17;
__io union { unsigned char TIFR1; struct { unsigned char TIFR1_Bit0:1, TIFR1_Bit1:1, TIFR1_Bit2:1, TIFR1_Bit3:1, TIFR1_Bit4:1, TIFR1_Bit5:1, TIFR1_Bit6:1, TIFR1_Bit7:1; }; struct { unsigned char TIFR1_TOV1:1, TIFR1_OCF1A:1, TIFR1_OCF1B:1, TIFR1_OCF1C:1, TIFR1_Dummy4:1, TIFR1_ICF1:1, TIFR1_Dummy6:1, TIFR1_Dummy7:1; }; } @ 0x16;
__io union { unsigned char TIFR0; struct { unsigned char TIFR0_Bit0:1, TIFR0_Bit1:1, TIFR0_Bit2:1, TIFR0_Bit3:1, TIFR0_Bit4:1, TIFR0_Bit5:1, TIFR0_Bit6:1, TIFR0_Bit7:1; }; struct { unsigned char TIFR0_TOV0:1, TIFR0_OCF0A:1, TIFR0_OCF0B:1, TIFR0_Dummy3:1, TIFR0_Dummy4:1, TIFR0_Dummy5:1, TIFR0_Dummy6:1, TIFR0_Dummy7:1; }; } @ 0x15;
__io union { unsigned char PORTG; struct { unsigned char PORTG_Bit0:1, PORTG_Bit1:1, PORTG_Bit2:1, PORTG_Bit3:1, PORTG_Bit4:1, PORTG_Bit5:1, PORTG_Bit6:1, PORTG_Bit7:1; }; struct { unsigned char PORTG_PORTG0:1, PORTG_PORTG1:1, PORTG_PORTG2:1, PORTG_PORTG3:1, PORTG_PORTG4:1, PORTG_PORTG5:1, PORTG_Dummy6:1, PORTG_Dummy7:1; }; } @ 0x14;
__io union { unsigned char DDRG; struct { unsigned char DDRG_Bit0:1, DDRG_Bit1:1, DDRG_Bit2:1, DDRG_Bit3:1, DDRG_Bit4:1, DDRG_Bit5:1, DDRG_Bit6:1, DDRG_Bit7:1; }; struct { unsigned char DDRG_DDG0:1, DDRG_DDG1:1, DDRG_DDG2:1, DDRG_DDG3:1, DDRG_DDG4:1, DDRG_DDG5:1, DDRG_Dummy6:1, DDRG_Dummy7:1; }; } @ 0x13;
__io union { unsigned char PING; struct { unsigned char PING_Bit0:1, PING_Bit1:1, PING_Bit2:1, PING_Bit3:1, PING_Bit4:1, PING_Bit5:1, PING_Bit6:1, PING_Bit7:1; }; struct { unsigned char PING_PING0:1, PING_PING1:1, PING_PING2:1, PING_PING3:1, PING_PING4:1, PING_PING5:1, PING_Dummy6:1, PING_Dummy7:1; }; } @ 0x12;
__io union { unsigned char PORTF; struct { unsigned char PORTF_Bit0:1, PORTF_Bit1:1, PORTF_Bit2:1, PORTF_Bit3:1, PORTF_Bit4:1, PORTF_Bit5:1, PORTF_Bit6:1, PORTF_Bit7:1; }; struct { unsigned char PORTF_PORTF0:1, PORTF_PORTF1:1, PORTF_PORTF2:1, PORTF_PORTF3:1, PORTF_PORTF4:1, PORTF_PORTF5:1, PORTF_PORTF6:1, PORTF_PORTF7:1; }; } @ 0x11;
__io union { unsigned char DDRF; struct { unsigned char DDRF_Bit0:1, DDRF_Bit1:1, DDRF_Bit2:1, DDRF_Bit3:1, DDRF_Bit4:1, DDRF_Bit5:1, DDRF_Bit6:1, DDRF_Bit7:1; }; struct { unsigned char DDRF_DDF0:1, DDRF_DDF1:1, DDRF_DDF2:1, DDRF_DDF3:1, DDRF_DDF4:1, DDRF_DDF5:1, DDRF_DDF6:1, DDRF_DDF7:1; }; } @ 0x10;
__io union { unsigned char PINF; struct { unsigned char PINF_Bit0:1, PINF_Bit1:1, PINF_Bit2:1, PINF_Bit3:1, PINF_Bit4:1, PINF_Bit5:1, PINF_Bit6:1, PINF_Bit7:1; }; struct { unsigned char PINF_PINF0:1, PINF_PINF1:1, PINF_PINF2:1, PINF_PINF3:1, PINF_PINF4:1, PINF_PINF5:1, PINF_PINF6:1, PINF_PINF7:1; }; } @ 0x0F;
__io union { unsigned char PORTE; struct { unsigned char PORTE_Bit0:1, PORTE_Bit1:1, PORTE_Bit2:1, PORTE_Bit3:1, PORTE_Bit4:1, PORTE_Bit5:1, PORTE_Bit6:1, PORTE_Bit7:1; }; struct { unsigned char PORTE_PORTE0:1, PORTE_PORTE1:1, PORTE_PORTE2:1, PORTE_PORTE3:1, PORTE_PORTE4:1, PORTE_PORTE5:1, PORTE_PORTE6:1, PORTE_PORTE7:1; }; } @ 0x0E;
__io union { unsigned char DDRE; struct { unsigned char DDRE_Bit0:1, DDRE_Bit1:1, DDRE_Bit2:1, DDRE_Bit3:1, DDRE_Bit4:1, DDRE_Bit5:1, DDRE_Bit6:1, DDRE_Bit7:1; }; struct { unsigned char DDRE_DDE0:1, DDRE_DDE1:1, DDRE_DDE2:1, DDRE_DDE3:1, DDRE_DDE4:1, DDRE_DDE5:1, DDRE_DDE6:1, DDRE_DDE7:1; }; } @ 0x0D;
__io union { unsigned char PINE; struct { unsigned char PINE_Bit0:1, PINE_Bit1:1, PINE_Bit2:1, PINE_Bit3:1, PINE_Bit4:1, PINE_Bit5:1, PINE_Bit6:1, PINE_Bit7:1; }; struct { unsigned char PINE_PINE0:1, PINE_PINE1:1, PINE_PINE2:1, PINE_PINE3:1, PINE_PINE4:1, PINE_PINE5:1, PINE_PINE6:1, PINE_PINE7:1; }; } @ 0x0C;
__io union { unsigned char PORTD; struct { unsigned char PORTD_Bit0:1, PORTD_Bit1:1, PORTD_Bit2:1, PORTD_Bit3:1, PORTD_Bit4:1, PORTD_Bit5:1, PORTD_Bit6:1, PORTD_Bit7:1; }; struct { unsigned char PORTD_PORTD0:1, PORTD_PORTD1:1, PORTD_PORTD2:1, PORTD_PORTD3:1, PORTD_PORTD4:1, PORTD_PORTD5:1, PORTD_PORTD6:1, PORTD_PORTD7:1; }; } @ 0x0B;
__io union { unsigned char DDRD; struct { unsigned char DDRD_Bit0:1, DDRD_Bit1:1, DDRD_Bit2:1, DDRD_Bit3:1, DDRD_Bit4:1, DDRD_Bit5:1, DDRD_Bit6:1, DDRD_Bit7:1; }; struct { unsigned char DDRD_DDD0:1, DDRD_DDD1:1, DDRD_DDD2:1, DDRD_DDD3:1, DDRD_DDD4:1, DDRD_DDD5:1, DDRD_DDD6:1, DDRD_DDD7:1; }; } @ 0x0A;
__io union { unsigned char PIND; struct { unsigned char PIND_Bit0:1, PIND_Bit1:1, PIND_Bit2:1, PIND_Bit3:1, PIND_Bit4:1, PIND_Bit5:1, PIND_Bit6:1, PIND_Bit7:1; }; struct { unsigned char PIND_PIND0:1, PIND_PIND1:1, PIND_PIND2:1, PIND_PIND3:1, PIND_PIND4:1, PIND_PIND5:1, PIND_PIND6:1, PIND_PIND7:1; }; } @ 0x09;
__io union { unsigned char PORTC; struct { unsigned char PORTC_Bit0:1, PORTC_Bit1:1, PORTC_Bit2:1, PORTC_Bit3:1, PORTC_Bit4:1, PORTC_Bit5:1, PORTC_Bit6:1, PORTC_Bit7:1; }; struct { unsigned char PORTC_PORTC0:1, PORTC_PORTC1:1, PORTC_PORTC2:1, PORTC_PORTC3:1, PORTC_PORTC4:1, PORTC_PORTC5:1, PORTC_PORTC6:1, PORTC_PORTC7:1; }; } @ 0x08;
__io union { unsigned char DDRC; struct { unsigned char DDRC_Bit0:1, DDRC_Bit1:1, DDRC_Bit2:1, DDRC_Bit3:1, DDRC_Bit4:1, DDRC_Bit5:1, DDRC_Bit6:1, DDRC_Bit7:1; }; struct { unsigned char DDRC_DDC0:1, DDRC_DDC1:1, DDRC_DDC2:1, DDRC_DDC3:1, DDRC_DDC4:1, DDRC_DDC5:1, DDRC_DDC6:1, DDRC_DDC7:1; }; } @ 0x07;
__io union { unsigned char PINC; struct { unsigned char PINC_Bit0:1, PINC_Bit1:1, PINC_Bit2:1, PINC_Bit3:1, PINC_Bit4:1, PINC_Bit5:1, PINC_Bit6:1, PINC_Bit7:1; }; struct { unsigned char PINC_PINC0:1, PINC_PINC1:1, PINC_PINC2:1, PINC_PINC3:1, PINC_PINC4:1, PINC_PINC5:1, PINC_PINC6:1, PINC_PINC7:1; }; } @ 0x06;
__io union { unsigned char PORTB; struct { unsigned char PORTB_Bit0:1, PORTB_Bit1:1, PORTB_Bit2:1, PORTB_Bit3:1, PORTB_Bit4:1, PORTB_Bit5:1, PORTB_Bit6:1, PORTB_Bit7:1; }; struct { unsigned char PORTB_PORTB0:1, PORTB_PORTB1:1, PORTB_PORTB2:1, PORTB_PORTB3:1, PORTB_PORTB4:1, PORTB_PORTB5:1, PORTB_PORTB6:1, PORTB_PORTB7:1; }; } @ 0x05;
__io union { unsigned char DDRB; struct { unsigned char DDRB_Bit0:1, DDRB_Bit1:1, DDRB_Bit2:1, DDRB_Bit3:1, DDRB_Bit4:1, DDRB_Bit5:1, DDRB_Bit6:1, DDRB_Bit7:1; }; struct { unsigned char DDRB_DDB0:1, DDRB_DDB1:1, DDRB_DDB2:1, DDRB_DDB3:1, DDRB_DDB4:1, DDRB_DDB5:1, DDRB_DDB6:1, DDRB_DDB7:1; }; } @ 0x04;
__io union { unsigned char PINB; struct { unsigned char PINB_Bit0:1, PINB_Bit1:1, PINB_Bit2:1, PINB_Bit3:1, PINB_Bit4:1, PINB_Bit5:1, PINB_Bit6:1, PINB_Bit7:1; }; struct { unsigned char PINB_PINB0:1, PINB_PINB1:1, PINB_PINB2:1, PINB_PINB3:1, PINB_PINB4:1, PINB_PINB5:1, PINB_PINB6:1, PINB_PINB7:1; }; } @ 0x03;
__io union { unsigned char PORTA; struct { unsigned char PORTA_Bit0:1, PORTA_Bit1:1, PORTA_Bit2:1, PORTA_Bit3:1, PORTA_Bit4:1, PORTA_Bit5:1, PORTA_Bit6:1, PORTA_Bit7:1; }; struct { unsigned char PORTA_PORTA0:1, PORTA_PORTA1:1, PORTA_PORTA2:1, PORTA_PORTA3:1, PORTA_PORTA4:1, PORTA_PORTA5:1, PORTA_PORTA6:1, PORTA_PORTA7:1; }; } @ 0x02;
__io union { unsigned char DDRA; struct { unsigned char DDRA_Bit0:1, DDRA_Bit1:1, DDRA_Bit2:1, DDRA_Bit3:1, DDRA_Bit4:1, DDRA_Bit5:1, DDRA_Bit6:1, DDRA_Bit7:1; }; struct { unsigned char DDRA_DDA0:1, DDRA_DDA1:1, DDRA_DDA2:1, DDRA_DDA3:1, DDRA_DDA4:1, DDRA_DDA5:1, DDRA_DDA6:1, DDRA_DDA7:1; }; } @ 0x01;
__io union { unsigned char PINA; struct { unsigned char PINA_Bit0:1, PINA_Bit1:1, PINA_Bit2:1, PINA_Bit3:1, PINA_Bit4:1, PINA_Bit5:1, PINA_Bit6:1, PINA_Bit7:1; }; struct { unsigned char PINA_PINA0:1, PINA_PINA1:1, PINA_PINA2:1, PINA_PINA3:1, PINA_PINA4:1, PINA_PINA5:1, PINA_PINA6:1, PINA_PINA7:1; }; } @ 0x00;

#pragma language=restore





 


   


   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   


   

   

   


   

   

   


   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   



 

 













 		

 		

 		

 		

 		

 		


void initbootuart()
{
  UBRR0L = 1;
  UCSR0B = (1 << 4) |
                     (1 << 3); 
}


void sendchar(char c)
{
  UDR0 = c;                                   
  while (!(UCSR0A & (1 << 6)));
  UCSR0A |= (1 << 6);          
}


char recchar(void)
{
  while(!(UCSR0A & (1 << 7)));  
  return UDR0;
}
