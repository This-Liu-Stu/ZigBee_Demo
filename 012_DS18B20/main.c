#include "ioCC2530.h"

#include "string.h"
#include "Delay.h"
#include "uart.h"
#include "DHT11.h"
#include "LCD.h"

#define MAX_LEN 100     //串口接收最大范围100

int data_len = 0;
int receive_state = 0;
char Receive[MAX_LEN] = {0};
unsigned char tempData[2];

void main()
{
  char str[9]="DS18B20";
  char strTemp[30];
  float fTemp;
  InitUart();
  P0SEL &= 0x7F;  //DS18B20引脚初始化
  
  while(1)
  {
    meset(strTemp)
  }
}