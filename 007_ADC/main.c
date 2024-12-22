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
    ADCCON3=0x31;       //00 内部参考电压   11 512抽取率（转换速度）   0000 序列通道选择AIN0    
    ADCCON1 |= 0x30;    //设置为STSEL为11
    ADCCON1 |= 0x40;    //转换开启标志
    
    while(!(ADCCON1 & 0x80));   //ADCCON1 & 0x80判断最高位是否为1，为1代表ADC转换结束，0则尚未结束
    
    ADC_Value = ADCL>>2;              //ADCL 7-2为数据位
    ADC_Value |= (((int)ADCH)<<8);     //合并ADCH + ADCL
    Delays();
  }
  
}