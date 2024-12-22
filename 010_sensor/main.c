#include "ioCC2530.h"
#include "stdio.h"
#include "string.h"

#define LED P1_0
#define SENSOR P0_1

char send_date[20];

void DelayMs(unsigned int time)
{ 
  unsigned int j,i;
  for(j=0;j<time;j++)
    for(i=0;i<535;i++);
}

void InitIO()
{
  P1DIR |= 0x01;  //01 Êä³ö
  P0DIR &= ~0x02; //1111 1101 ÊäÈë
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

void main(void)
{
  unsigned int i = 0;
  InitIO();
  InitUart();
  while(1)
  {
    LED = 1;
    if(SENSOR == 0)
    {
      DelayMs(10);
      if(SENSOR == 0)
      {
        sprintf(send_date,"Now state of key is %d",SENSOR);
        Send_String(send_date, strlen(send_date));
        memset(send_date, 0, sizeof(send_date)); 
        for(i=0;i<10;i++)
        {
          LED = ~LED;
          DelayMs(100);
        }
      }
    }
  }
}
