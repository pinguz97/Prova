




#include "init_PIC.h"


void init_PORTS(void)
{
    LATB = 0;
    PORTB = 0;
    TRISB = 0xFF;
    
    LATC = 0;
    PORTC = 0;
        /*Configure pins*/
   // TRISC6 = 0;
    //TRISC7 = 1;
    
    return;
}