#include <ioCC2530.h>

#define LED0 P1_0

unsigned int counter = 0;

void Init_Timer()
{
  P1SEL &= ~0x01;
  P1DIR = 0x01;
  CLKCONCMD &= ~0x7F;
  while(CLKCONCMD & 0x40);
  T1IE = 1;
  T1CTL = 0x05;
  LED0 = 0;
  EA = 1;
}

void main()
{
  Init_Timer();
  while(1);

}

#pragma vector = T1_VECTOR
__interrupt void T1_ISR()
{
  IRCON = 0x00;
  if(counter < 100)
    counter++;
  else
  {
    LED0 = !LED0;
    counter = 0;
  }
}