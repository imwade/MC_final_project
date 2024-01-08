#include <xc.h>

void INTERRUPT_Initialize (void)
{
    
    RCONbits.IPEN = 1;      //enable Interrupt Priority mode
    INTCONbits.GIEH = 1;    //enable high priority interrupt
    INTCONbits.GIEL = 1;     //disable low priority interrupt
    
    INTCON2bits.RBIP = 1;
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;
    
    INTCON3bits.INT1IP = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT1IE = 1;
}

