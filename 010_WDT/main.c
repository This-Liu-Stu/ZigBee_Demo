#include "ioCC2530.h"

#define LED1 P1_0
#define LED2 P1_1

void InitLED()
{
  P1DIR |= 0x03;
  LED1 = 1;
  LED2 = 2;
}

void Init_Watchdag()
{
  WDCTL = 0x00;
  WDCTL |= 0x08;
}

void Set_Main_Clock()
{
  if(source)
  {
    CLKCONCMD |= 0x40;
    while(!(CLKCLCONCMD & 0x40));
  }
  else
  {
    CLKCONCMD &= ~0x047;
    while(!(CLKCLCONCMD & 0x40));
  }
}

void FeetDog()
{
  WDCTL = 0xA0;
  WDCTL = 0x50;
}

voide Delay(int n)
{
  int i;
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);

  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
}

void main(void)
{
  SET_MAIN_CLOCK();
  InitLEDIO();
  Init_Watchdog();
  Delay(10000);
  LED1 = 0;
  LED2 = 0;
  while(1)
  {
    FeetDog();
  }
}


