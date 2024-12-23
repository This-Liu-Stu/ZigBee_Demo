#include "ioCC2530.h"

#define LED1 P1_0
#define LED2 P1_1
#define KEY P0_1

//��ʱ����
void delay(void)
{
  unsigned int i;
  for(i=0 ; i<50000 ; i++)  asm("nop");
}

void IO_Init()
{
  P1DIR |= 0x03;
  P1 |= 0x03;   //ȫ��Ϩ��
  P0SEL &= ~0x03;
  P0DIR &= ~0x03;
  P0INP |= 0x03;
}

void InitINT()
{
  P0SEL &= ~0x02;
  P0INP |= 0x02;
  P0IEN |= 0x02;
  PICTL |= 0x01;
  EA = 1;
  IEN1 |= 0x20;
  P0IFG &= 0x00;
}

unsigned char count = 0;

int main()
{
  InitINT();
  IO_Init();
  while(1)
  {
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

#pragma vector = P1INT_VECTOR

__interrupt void P0_INT()
{ 
  P0IFG = 0;
  P0IF = 0;
  delay();
  if(KEY == 0)
    while(KEY == 0);
   count++;
  if(count > 3) count = 0;
}