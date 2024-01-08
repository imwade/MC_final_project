#ifndef _UART_H
#define _UART_H
      
void UART_Initialize(void);
char * GetString();
int Get_complete_state();
void clear_complete();
void UART_Write(unsigned char data);
void UART_Write_Text(char* text);
void ClearBuffer();
void MyusartRead();

#endif