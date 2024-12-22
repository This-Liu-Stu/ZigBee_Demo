#include "ds18b20.h" 

#define Ds18b20IO P0_7       //�¶ȴ���������

void Delay_us(unsigned int k)//us��ʱ����
{
    T1CC0L = 0x06; 
    T1CC0H = 0x00; 
    T1CTL = 0x02; //ģģʽ������Ƶ��
    while(k)
    { 
        while(!(T1CNTL >= 0x04));
        k--;
    }
    T1CTL = 0x00;  //�رն�ʱ��
}

void Delay_ms(unsigned int k)
{
    T1CC0L = 0xe8;
    T1CC0H = 0x03;
    T1CTL = 0x0a; //ģģʽ 32��Ƶ
    while(k)
    {
        while(!((T1CNTL >= 0xe8)&&(T1CNTH >= 0x03)));
        k--;
    }
    T1CTL = 0x00; //�رն�ʱ��
}

void Delay_s(unsigned int k)
{
    while(k)
    {
        Delay_ms(1000);
        k--;
    }
}

//ʱ��Ƶ��Ϊ32M
void Ds18b20Delay(unsigned int k)
{
    unsigned int i,j;
    for(i=0;i<k;i++)
        for(j=0;j<2;j++);
}

void Ds18b20InputInitial(void)//���ö˿�Ϊ����
{
   
}

void Ds18b20OutputInitial(void)//���ö˿�Ϊ���
{
    
}

//ds18b20��ʼ��  ��ʼ���ɹ�����0x00��ʧ�ܷ���0x01
unsigned char Ds18b20Initial(void)
{





















}

void Ds18b20Write(unsigned char infor)
{




















}

unsigned char Ds18b20Read(void)
{


















}

//�¶ȶ�ȡ����
unsigned char ReadDs18B20(void) 
{
    unsigned char V1,V2;   //����ߵ�8λ ����
    unsigned char temp;    //�����¶Ȼ���Ĵ���
    
    Ds18b20Initial();
    Ds18b20Write(0xcc);    // ����������кŵĲ���
    Ds18b20Write(0x44);    // �����¶�ת��
    
    Ds18b20Initial();
    Ds18b20Write(0xcc);    //����������кŵĲ��� 
    Ds18b20Write(0xbe);    //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
    
    V1 = Ds18b20Read();    //��λ
    V2 = Ds18b20Read();    //��λ
    temp = ((V1 >> 4)+((V2 & 0x07)*16)); //ת������ 

    return temp;
}

//�¶ȶ�ȡ���� ��1λС��λ
float floatReadDs18B20(void) 
{



















}