#include "ioCC2530.h"

int ADC_Value;

void Delays(void){
  unsigned int temp;
  for(temp = 0; temp<500;temp++)  asm("nop");
}

void main()
{
  while(1)
  {
    ADCCON3=0x31;       //00 �ڲ��ο���ѹ   11 512��ȡ�ʣ�ת���ٶȣ�   0000 ����ͨ��ѡ��AIN0    
    ADCCON1 |= 0x30;    //����ΪSTSELΪ11
    ADCCON1 |= 0x40;    //ת��������־
    
    while(!(ADCCON1 & 0x80));   //ADCCON1 & 0x80�ж����λ�Ƿ�Ϊ1��Ϊ1����ADCת��������0����δ����
    
    ADC_Value = ADCL>>2;              //ADCL 7-2Ϊ����λ
    ADC_Value |= (((int)ADCH)<<8);     //�ϲ�ADCH + ADCL
    Delays();
  }
  
}