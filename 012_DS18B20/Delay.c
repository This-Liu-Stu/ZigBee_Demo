#include "Delay.h"

void Delay_2us()
{
  asm("nop");
  asm("nop");
}

void Delay_10us()
{
  Delay_2us();
  Delay_2us();
  Delay_2us();
  Delay_2us();
  Delay_2us();
}


void Delay_nms(unsigned int i)
{
  char x;
  while(i>0)
  {
    for(x=0; x<100 ; x++)
      Delay_10us();
    i--;
  }
}

