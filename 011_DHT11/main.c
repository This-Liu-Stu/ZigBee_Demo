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
  InitUart();
  LCD_Init();
  LCD_CLS();
  LCD_welcome();
  Delay_nms(1500);
  LCD_CLS();
  while(1)
  {
    Get_DHT();
    Send_String(Temp_temp,strlen(Temp_temp));
    Send_String(DHT11_DATA,2);
    Send_String(" ",1);
    Send_String(Humi_temp,strlen(Humi_temp));
    Send_String(DHT11_DATA+2,2);
    Send_String("\r\n",2);
    LCD_P16x16Ch(0,0,2);       //显示温度
    LCD_P16x16Ch(16*1,0,3);
    char temp[3];
    strncpy(temp, DHT11_DATA, 2);
    temp[2] = '\0';
    LCD_P8x16Str(16*2,0,temp);
    
    LCD_P16x16Ch(0,2,4);       //显示湿度
    LCD_P16x16Ch(16*1,2,5);
    char humi[3];
    strncpy(humi, DHT11_DATA + 2, 2);
    humi[2] = '\0';
    LCD_P8x16Str(16*2,2,humi);
    Delay_nms(500);
  }
}