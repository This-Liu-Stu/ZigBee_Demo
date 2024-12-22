#include "ioCC2530.h"

#define LED1 P1_0
#define LED2 P1_1
#define KEY P0_1

//延时函数
void delay(void)
{
  unsigned int i;
  for(i=0 ; i<50000 ; i++)  asm("nop");
}

void IO_Init()
{
  P1DIR |= 0x03;
  P1 |= 0x03;   //全部熄灭
  P0SEL &= ~0x03;
  P0DIR &= ~0x03;
  P0INP |= 0x03;
}

int main()
{
  unsigned char count = 0;
  IO_Init();
  while(1)
  {
    if(!KEY)
    {
      delay();
      if(!KEY)
        while(!KEY);
      count++;
    }
    switch(count)
    {
      case 0:
        P1 |= 0x03;
        break;
      case 1:
        P1 &= ~0x01;
        break;
      case 2:
        P1 |= 0x03;
        P1 &= ~0x02;
        break;
      case 3:
        P1 &= ~0x03;
        break;
      default:
        count = 0;
        break;
    }
  }
}