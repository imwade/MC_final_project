#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// using namespace std;

#define _XTAL_FREQ 4000000

#define LED LATAbits.LATA0



char string[20] = {0};
char str[20] = {0};
int state;
int complete;

typedef struct 
{
    int code;
    int count;
} morse_code;

morse_code alphabet_to_code(char c);
char code_to_alphabet(morse_code mc);

void state1_output(int input_code, int input_count)
{
    morse_code mc;
    mc.code = input_code;
    mc.count = input_count;
    
    char a = code_to_alphabet(mc);
    UART_Write(a);
}

void bee_led_output(morse_code in);


void __interrupt(high_priority) H_ISR()
{
        UART_Write_Text("interrupt");
    if  (INTCONbits.INT0IF && state == 1) // state == 1, button input
    {
        while(1)
        {
            UART_Write_Text("state = 1");
            int input_code = 0;
            int input_count = 0;
            int clock = 0;
            while (PORTBbits.RB1 == 0)
            {
                //led on
                //bee on
                for(int i=40;i>0 && PORTBbits.RB1==0 ;i--)
                {
                    TMR2 = 0;
                    T2CONbits.TMR2ON = 1;
                    PIR1bits.TMR2IF = 0;
                    while (PIR1bits.TMR2IF == 0);
                }
                if (PORTBbits.RB1 == 0) clock++;
            }
            TMR2 = 0;
            T2CONbits.TMR2ON = 0;
            PIR1bits.TMR2IF = 0;
            input_code = input_code << 1;
            input_count++;
            
            if (clock == 0)
            {
                input_code += 0;
            }
            else
            {
                input_code += 1;
            }
            
            clock = 0;
            while (PORTBbits.RB1 == 1)
            {
                //led on
                //bee on
                for(int i=40;i>0 && PORTBbits.RB1==1;i--)
                {
                    TMR2 = 0;
                    T2CONbits.TMR2ON = 1;
                    PIR1bits.TMR2IF = 0;
                    while (PIR1bits.TMR2IF == 0);
                }
                if(PORTBbits.RB1 == 1){
                    clock++;
                
                    if(clock == 3)
                    {
                        state1_output(input_code, input_count);
                    }
                    else if(clock == 6)
                    {
                        //output space
                        INTCONbits.INT0IF = 0;
                        return;
                    }
                }
            }
        }
        INTCONbits.INT0IF = 0;
    }
    
    return;
}

void output(void)
{
    for (int i=0; str[i] >=48 ; i++)
    {
        bee_led_output( alphabet_to_code(str[i]) );
        str[i] = '\0';
    }
}

void bee_led_output(morse_code in)
{
    int count = in.count;
    int code = in.code;
    int mask = 0x10;
    
    if (count == 0) // space
    {
        __delay_ms(3000);
        return;
    }
    
    for(int i=count-1; i>=0; i--, code<<=1)
    {
        UART_Write_Text("i = ");
        UART_Write(i + 48);
        int signal = (code & mask) >> 4;
        if (signal == 0)
        {
             LED = 1;
            __delay_ms(250);
             LED = 0;
        }
        else
        {
             LED = 1;
            __delay_ms(500);
             LED = 0;
        }
        __delay_ms(250); // in alphabet
    }
    __delay_ms(750); // between alphabets
    
    return;
}

morse_code alphabet_to_code(char c)
{
    morse_code rv;
    c |= 32;
    rv.code = 0;
    rv.count = 0;
    switch (c)
    {
        case ' ':
            break;
        
        case 'a':
            rv.code = 0b01000;
            rv.count = 2;
            break;
            
        case 'b':
            rv.code = 0b10000;
            rv.count = 4;
            break;
        
        case 'c':
            rv.code = 0b10100;
            rv.count = 4;
            break;
        
        case 'd':
            rv.code = 0b10000;
            rv.count = 3;
            break;
        
        case 'e':
            rv.code = 0b00000;
            rv.count = 1;
            break;
        
        case 'f':
            rv.code = 0b00100;
            rv.count = 4;
            break;
        
        case 'g':
            rv.code = 0b11000;
            rv.count = 3;
            break;
        
        case 'h':
            rv.code = 0b00000;
            rv.count = 4;
            break;
        
        case 'i':
            rv.code = 0b00000;
            rv.count = 2;
            break;
        
        case 'j':
            rv.code = 0b01110;
            rv.count = 4;
            break;
        
        case 'k':
            rv.code = 0b10100;
            rv.count = 3;
            break;

        case 'l':
            rv.code = 0b01000;
            rv.count = 4;
            break;

        case 'm':
            rv.code = 0b11000;
            rv.count = 2;
            break;

        case 'n':
            rv.code = 0b10000;
            rv.count = 2;
            break;

        case 'o':
            rv.code = 0b11100;
            rv.count = 3;
            break;

        case 'p':
            rv.code = 0b01100;
            rv.count = 4;
            break;

        case 'q':
            rv.code = 0b11010;
            rv.count = 4;
            break;

        case 'r':
            rv.code = 0b01000;
            rv.count = 3;
            break;

        case 's':
            rv.code = 0b00000;
            rv.count = 3;
            break;

        case 't':
            rv.code = 0b10000;
            rv.count = 1;
            break;

        case 'u':
            rv.code = 0b00100;
            rv.count = 3;
            break;

        case 'v':
            rv.code = 0b00010;
            rv.count = 4;
            break;

        case 'w':
            rv.code = 0b01100;
            rv.count = 3;
            break;
        
        case 'x':
            rv.code = 0b10010;
            rv.count = 4;
            break;

        case 'y':
            rv.code = 0b10110;
            rv.count = 4;
            break;

        case 'z':
            rv.code = 0b11000;
            rv.count = 4;
            break;
        
        case '0':
            rv.code = 0b11111;
            rv.count = 5;
            break;
        
        case '1':
            rv.code = 0b01111;
            rv.count = 5;
            break;
        
        case '2':
            rv.code = 0b00111;
            rv.count = 5;
            break;
        
        case '3':
            rv.code = 0b00011;
            rv.count = 5;
            break;
        
        case '4':
            rv.code = 0b00001;
            rv.count = 5;
            break;
        
        case '5':
            rv.code = 0b00000;
            rv.count = 5;
            break;
        
        case '6':
            rv.code = 0b10000;
            rv.count = 5;
            break;
        
        case '7':
            rv.code = 0b11000;
            rv.count = 5;
            break;
        
        case '8':
            rv.code = 0b11100;
            rv.count = 5;
            break;
        
        case '9':
            rv.code = 0b11110;
            rv.count = 5;
            break;
    }
    return rv;
}


void main(void) 
{
    
    SYSTEM_Initialize();
    state = 0;
    char * check = "your string is : ";
    
    while(1) {
        
        if(state == 0){
            //UART_Write_Text("STATE 0");
            strcpy(string, GetString());
            complete = Get_complete_state();
            if(complete == 1 ){
                UART_Write_Text(check);
                UART_Write_Text(string);
                strcpy(str,string);
                UART_Write_Text("\r\n\n");
                
                output();
                
                clear_complete();
                ClearBuffer();
            } else {

            }
        }
}
    
    return;
}
    
char code_to_alphabet(morse_code mc)
{
    char rc;
    switch (mc.count)
    {
        case 1:
            switch (mc.code)
            {
                case 0b10000:
                    rc = 't';
                    break;
                case 0b00000:
                    rc = 'e';
                    break;
            }
            break;
        case 2:
            switch (mc.code)
            {
                case 0b01000:
                    rc = 'a';
                    break;
                case 0b00000:
                    rc = 'i';
                    break;
                case 0b11000:
                    rc = 'm';
                    break;
                case 0b10000:
                    rc = 'n';
                    break;
            }
            break;
         case 3:
            switch (mc.code)
            {
                case 0b10000:
                    rc = 'd';
                    break;
                case 0b11000:
                    rc = 'g';
                    break;
                case 0b10100:
                    rc = 'k';
                    break;
                case 0b11100:
                    rc = 'o';
                    break;
                case 0b01000:
                    rc = 'r';
                    break;
                case 0b00000:
                    rc = 's';
                    break;
                case 0b00100:
                    rc = 'u';
                    break;
                case 0b01100:
                    rc = 'w';
                    break;
            }
            break;
        case 4:
            switch (mc.code)
            {
                case 0b10000:
                    rc = 'b';
                    break;
                case 0b10100:
                    rc = 'c';
                    break;
                case 0b00100:
                    rc = 'f';
                    break;
                case 0b00000:
                    rc = 'h';
                    break;
                case 0b01110:
                    rc = 'j';
                    break;
                case 0b01000:
                    rc = 'l';
                    break;
                case 0b01100:
                    rc = 'p';
                    break;
                case 0b11010:
                    rc = 'q';
                    break;
                case 0b00010:
                    rc = 'v';
                    break;
                case 0b10010:
                    rc = 'x';
                    break;
                case 0b10110:
                    rc = 'y';
                    break;
                case 0b11000:
                    rc = 'z';
                    break;
            }
        case 5:
            switch (mc.code)
            {
                case 0b01111:
                    rc = '1';
                    break;
                case 0b00111:
                    rc = '2';
                    break;
                case 0b00011:
                    rc = '3';
                    break;
                case 0b00001:
                    rc = '4';
                    break;
                case 0b00000:
                    rc = '5';
                    break;
                case 0b10000:
                    rc = '6';
                    break;
                case 0b11000:
                    rc = '7';
                    break;
                case 0b11100:
                    rc = '8';
                    break;
                case 0b11110:
                    rc = '9';
                    break;
                case 0b11111:
                    rc = '0';
                    break;
            }
            break;
    }
    
    return rc;
}