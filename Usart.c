

#include "Usart.h"



void UART_init(){
    
    SPBRG = (_XTAL_FREQ/_BAUD_RATE/16)-1;
    /*Configure transmit control register*/
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    
    /*Configure receive control register*/
    RCSTAbits.CREN = 1;
    RCSTAbits.RX9 = 0;
    
    /*Enable serial port*/
    RCSTAbits.SPEN = 1;
    
    TRISC6 = 0;
    TRISC7 = 1;
    
    /*interrupts*/

    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    //PIR1bits.TXIF = 0;
    //PIE1bits.TXIE = 1;
    return;
}
//void init_USART(void)
//{
//    //From Datasheet, in case of Asynchronous Mode:
//    //Desired Baud Rate = FOSC / (64 (X + 1)), if TXSTA<BRGH> = 0 or
//    //Desired Baud Rate = FOSC / (16 (X + 1)), if TXSTA<BRGH> = 1 
//    
//    // X is the nearest integer value for the SPBRG register needed to obtain the desired baud rate
//    
//    //The choice depends on 
//    // - Fosc 
//    // - Error = (Calculated Baud Rate - Desired Baud Rate)/Desired Baud Rate
//    
//    // In this case with Fosc = 4 MHz and 9600 bps as desired baud rate
//    
//    //SPBRG = ( (Fosc / Desired Baud Rate) / 16 ) - 1
//    
//    SPBRG = round(((_XTAL_FREQ / _BAUD_RATE)/16)-1); // baud rate
//        
//	TXSTAbits.TX9=0;   //TX 8 bits data
//    TXSTAbits.TXEN=1;  //TX enable
//    TXSTAbits.SYNC=0;  //Asynchronous Mode
//    TXSTAbits.BRGH=1;  //High baud rate bit
//    RCSTAbits.SPEN=1;  //Serial Port enable
//    RCSTAbits.RX9=0;   //RX 8 bits data
//    RCSTAbits.CREN=1;  //RX enable
//}

//void init_PORTS(void)          //PORTS configurations
//{
//    // PORTB
//    LATB    = 0;        //All pins off
//    PORTB   = 0;
//    TRISB   = 0xF0;     //All pins as input (default), RB0 (toggle led when RX char),
//                        //RB1, RB2, RB3 as output
//    
//    // PORTC
//    LATC    = 0;        //All pins off
//    PORTC   = 0;
//    TRISCbits.RC7 = 1;  //All pins as input (default), RC7 as Input (Usart RX)
//    TRISCbits.RC6 = 0;  //RC6 as output (Usart TX)
//        
//    return;
//}
////--------------------------------------------------


void UART_write(char c){
    
    TXREG = c;
    while(!TX_shift_reg_empty);
    
    return;
}

char UART_read(){
    
    if(RX_Overrun_Error | RX_Framing_Error){
    UART_DISABLE_RX();
    UART_ENABLE_RX();
    RCREG;
    RCREG;
    return 0x9F;
    }   
    else {
        return RCREG;
    }
}

_Bool UART_data_ready(){
    
    return RX_INTERRUPT_FLAG;

}

void UART_close(){
    
    UART_DISABLE_TX();
    UART_DISABLE_RX();
    UART_DISABLE_PORT();
    
    TX_INTERRUPT_ENABLE = 0;
    RX_INTERRUPT_ENABLE = 0;
    
    /*Clear RCREG buffer*/
    RCREG;
    RCREG;
}


_Bool UART_start_comm(){
    
    unsigned int elapsed_time = 0;
    unsigned int timeout = 2000;
    unsigned char Rx_Data = ' ';
    UART_write(0xF0);
    di();
    while((elapsed_time < timeout) && !PIR1bits.RCIF){
        __delay_ms(20);
        elapsed_time += 20;
    }
    if (PIR1bits.RCIF){
    Rx_Data = UART_read();
        if (Rx_Data == 0xA5){
             ei();
            return 1;
        }
    }
    else{
         ei();
         return 0;
    }
      
   
}




