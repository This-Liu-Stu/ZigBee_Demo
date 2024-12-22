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
    while(!DATA_PIN);   //���Ϊ�͵�ƽ���ȴ�
    Delay_10us();       //ÿһbit���ݶ���50us�͵�ƽʱ϶��ʼ
    Delay_10us();
    Delay_10us();
    temp = 0;
    if(DATA_PIN)        //���Ϊ�ߵ�ƽ��Ϊ1
    temp = 1;
    while(DATA_PIN);    //�ȴ���Ϊ�͵�ƽ������һ��λ�Ľ���
    ucharcomdata<<=1;
    ucharcomdata |= temp;
  }
}

void DHT11_Read()
{
  unsigned char T_data_H,T_data_L,H_data_H,H_data_L,checkdata;
  DATA_PIN = 0;     //�������͵͵�ƽ����18us
  Delay_nms(19);  //����18us
  DATA_PIN = 1;   //��������
  P0DIR &= ~0x80;
  Delay_10us();   //�ȴ�20-40us
  Delay_10us();
  Delay_10us();
  Delay_10us();
  if(!DATA_PIN)   //DHT11������Ӧ�ź�
  {
    while(!DATA_PIN);   //�ȴ���Ӧ�źŽ���
    while(DATA_PIN);    //�ȴ�DHT����
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