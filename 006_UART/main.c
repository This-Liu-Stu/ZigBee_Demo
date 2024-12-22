#include "ioCC2530.h"
#include <string.h>

#define LED0 P1_0
#define LED1 P1_1
#define MAX_LEN 100

int data_len = 0;
int receive_state = 0;
char Receive[MAX_LEN] = {0};

void LED_Init(){
  P1DIR |= 0x03;
  LED0 = 0;
  LED1 = 0;
}

void InitUart(){
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

void Send_String(char *Data, int len){
  for(int j = 0; j < len; j++){
    U0DBUF = *Data++;
    while(UTX0IF == 0); 
    UTX0IF = 0; 
  }
}

void main(){
  LED_Init();
  InitUart();
  while(1){
    if(receive_state == 1){
      Send_String(Receive, data_len);
      memset(Receive, 0, sizeof(Receive)); 
      data_len = 0; 
      receive_state = 0;
    }
  }
}

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

