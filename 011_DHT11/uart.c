#include "uart.h"

void InitUart()
{
  CLKCONCMD &=~0x40;
  while(CLKCONSTA & 0x40);
  CLKCONCMD &=~0x47;
  
  PERCFG = 0x3c;
  P0SEL = 0x3C;
  
  U0CSR |= 0x80;
  U0GCR |= 11;
  U0BAUD |= 216;
  
  UTX0IF = 0;
  U0CSR |= 0x40;
  IEN0 |= 0x84;
}

void Send_String(char *Data, int len)
{
  for(int j = 0; j < len; j++){
    U0DBUF = *Data++;
    while(UTX0IF == 0); 
    UTX0IF = 0; 
  }
}

/* ´®¿ÚÖÐ¶Ïº¯Êý
#pragma vector = URX0_VECTOR
__interrupt void UART0_ISR(){
  if (data_len < MAX_LEN - 1) {
    Receive[data_len] = U0DBUF; 
    if (U0DBUF == '#') {
      receive_state = 1; 
      data_len++; 
      Receive[data_len] = '\0'; 
    } else {
      data_len++;
    }
  }
  URX0IF = 0; 
}
*/