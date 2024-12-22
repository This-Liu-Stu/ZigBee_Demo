#include "ioCC2530.h"

char TempValue[6];

void AD_Init();
float GetAD(void);

int main()
{
  float temp = 0;
  int count = 0;
  for(count=0 ; count<64 ; count++)
  {
    temp += GetAD();
  }
  temp /= count;
  TempValue[0] = (unsigned char)(temp)/10+48;
  TempValue[1] = (unsigned char)(temp)%10+48;
  TempValue[2] = '.';
  TempValue[3] = (unsigned char)(temp*10)%10+48;  
  TempValue[4] = (unsigned char)(temp*100)%10+48;
  TempValue[5] = '\0';
  
  return 0;
}

void AD_Init()
{

  ADCCON3 = 0x3E;
  ADCCON1 |= 0x70;
}

float GetAD(void)
{
  unsigned int temp=0;
  AD_Init();
  while(!(ADCCON1&0x80));
  temp = ADCL>>4;
  temp |= (((unsigned int)ADCH)<<4);
  return (temp-1367.5)/4.5-4;
}