#include <xc.h>

void ADC_Initialize(void) {
  
}

int ADC_Read(int channel)
{
    int digital;
    
    ADCON0bits.CHS =  0x07; // Select Channe7
    ADCON0bits.GO = 1;
    ADCON0bits.ADON = 1;
    
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);
    return(digital);
}