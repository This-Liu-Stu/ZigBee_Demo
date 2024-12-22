#include "ioCC2530.h"

#define LED1 P1_0
#define LED2 P1_1
#define KEY P0_1

void LED_Init(void)
{
  P1DIR |= 0x03;
  led1 = 1;
  led2 = 2; 
} 

void SET_MAIN_CLOCK(source)
{
  if(source){
    CLKCONCMD |= 0x40;
    while(!(CLKCONSTA & 0x40));
  }
  else
  {
    CLKCONCMD &= ~0x47;
    while(!(CLKCONSTA & 0x40));
  }

}

void SET_LOW_CLOCK(source)
{
  (source==RC)?(CLKCONCMD |= 0x80):(CLKCONCMD &= ~0x80);

}

int main()
{
  SET_MAIN_CLOCK(CRYSTAL);
  SET_LOW_CLOCK(CRYSTAL);
  LED_Init();
  LEDBINK = 0;
  Init_Sleep_Timer();
  LEDGlint();
  Set_ST_Period(3);
  while(1)
  {
    if(LEDBLINK)
    {
      LEDGlint();
      Set_ST_Period(3);
      LED2 != LED2;
    }
    Delay(100);
  }
  return 0;
}