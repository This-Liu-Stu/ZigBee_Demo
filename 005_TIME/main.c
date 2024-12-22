#include "ioCC2530.h"

#define LED0 P1_0
#define LED1 P1_1

unsigned int t1_counter = 0;
unsigned int t3_counter = 0;

void IO_Init()
{
  P1SEL &= ~0x03;
  P1DIR = 0x03;
    
  LED0 = 1;
  LED1 = 1;
}

void Time_Init()
{
  CLKCONCMD &= ~0x7F;
  while(CLKCONSTA & 0x40);
  
  T1IE = 1;
  T1CTL = 0x05;
  
  T3IE = 1;
  T3CTL=0x7C;
  
  EA = 1;
}

void main()
{
  IO_Init();
  Time_Init();
  
  while(1)
  {
    
  }
 
}

#pragma vector = T1_VECTOR
__interrupt void T1_Int()
{
  IRCON = 0x00;
  t1_counter++;
  if(t1_counter == 1000)
  {
    t1_counter = 0;
    LED0 = !LED0;
  }
}

#pragma vector = T3_VECTOR
__interrupt void T3_Int()
{
  IRCON = 0x00;
  t3_counter++;
  if(t3_counter == 1000)
  {
    t3_counter = 0;
    LED1 = !LED1;
  }
}