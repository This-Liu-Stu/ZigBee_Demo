#include "DHT11.h"

char DHT11_DATA[4];
char Temp_temp[]="Temp:";
char Humi_temp[]="Humi:";

unsigned char temp; 
unsigned char temp_ge,temp_shi,humi_ge,humi_shi;
unsigned char ucharcomdata;

void DHT_CMD()
{
  unsigned char i;
  for(i=0 ; i<8 ; i++)
  {
    while(!DATA_PIN);   //如果为低电平，等待
    Delay_10us();       //每一bit数据都以50us低电平时隙开始
    Delay_10us();
    Delay_10us();
    temp = 0;
    if(DATA_PIN)        //如果为高电平就为1
    temp = 1;
    while(DATA_PIN);    //等待变为低电平，结束一个位的接收
    ucharcomdata<<=1;
    ucharcomdata |= temp;
  }
}

void DHT11_Read()
{
  unsigned char T_data_H,T_data_L,H_data_H,H_data_L,checkdata;
  DATA_PIN = 0;     //主机拉低低电平至少18us
  Delay_nms(19);  //至少18us
  DATA_PIN = 1;   //主机拉高
  P0DIR &= ~0x80;
  Delay_10us();   //等待20-40us
  Delay_10us();
  Delay_10us();
  Delay_10us();
  if(!DATA_PIN)   //DHT11发送响应信号
  {
    while(!DATA_PIN);   //等待响应信号结束
    while(DATA_PIN);    //等待DHT拉高
    DHT_CMD();
    H_data_H = ucharcomdata;
    DHT_CMD();
    H_data_L = ucharcomdata;
    DHT_CMD();
    T_data_H = ucharcomdata;
    DHT_CMD();
    T_data_L = ucharcomdata;
    DHT_CMD();
    checkdata = ucharcomdata;
    DATA_PIN = 1;
    temp = (T_data_H+T_data_L+H_data_H+H_data_L);

    if (temp == checkdata)
    {
      temp_shi = T_data_H/10;
      temp_ge = T_data_L%10;
      humi_shi = H_data_H/10;
      humi_ge = H_data_L%10;
    }
  }
  else
  {
    temp_ge = 0;
    temp_shi = 0;
    humi_ge = 0;
    humi_shi = 0;
  }
  P0DIR |= 0x80;
}

void Get_DHT()
{
  DHT11_Read();
  DHT11_DATA[0] = temp_shi + 0x30;
  DHT11_DATA[1] = temp_ge + 0x30;
  DHT11_DATA[2] = humi_shi + 0x30;
  DHT11_DATA[3] = humi_ge + 0x30;
}