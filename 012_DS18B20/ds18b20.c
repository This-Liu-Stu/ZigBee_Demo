#include "ds18b20.h" 

#define Ds18b20IO P0_7       //温度传感器引脚

void Delay_us(unsigned int k)//us延时函数
{
    T1CC0L = 0x06; 
    T1CC0H = 0x00; 
    T1CTL = 0x02; //模模式，不分频；
    while(k)
    { 
        while(!(T1CNTL >= 0x04));
        k--;
    }
    T1CTL = 0x00;  //关闭定时器
}

void Delay_ms(unsigned int k)
{
    T1CC0L = 0xe8;
    T1CC0H = 0x03;
    T1CTL = 0x0a; //模模式 32分频
    while(k)
    {
        while(!((T1CNTL >= 0xe8)&&(T1CNTH >= 0x03)));
        k--;
    }
    T1CTL = 0x00; //关闭定时器
}

void Delay_s(unsigned int k)
{
    while(k)
    {
        Delay_ms(1000);
        k--;
    }
}

//时钟频率为32M
void Ds18b20Delay(unsigned int k)
{
    unsigned int i,j;
    for(i=0;i<k;i++)
        for(j=0;j<2;j++);
}

void Ds18b20InputInitial(void)//设置端口为输入
{
   
}

void Ds18b20OutputInitial(void)//设置端口为输出
{
    
}

//ds18b20初始化  初始化成功返回0x00，失败返回0x01
unsigned char Ds18b20Initial(void)
{





















}

void Ds18b20Write(unsigned char infor)
{




















}

unsigned char Ds18b20Read(void)
{


















}

//温度读取函数
unsigned char ReadDs18B20(void) 
{
    unsigned char V1,V2;   //定义高低8位 缓冲
    unsigned char temp;    //定义温度缓冲寄存器
    
    Ds18b20Initial();
    Ds18b20Write(0xcc);    // 跳过读序号列号的操作
    Ds18b20Write(0x44);    // 启动温度转换
    
    Ds18b20Initial();
    Ds18b20Write(0xcc);    //跳过读序号列号的操作 
    Ds18b20Write(0xbe);    //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
    
    V1 = Ds18b20Read();    //低位
    V2 = Ds18b20Read();    //高位
    temp = ((V1 >> 4)+((V2 & 0x07)*16)); //转换数据 

    return temp;
}

//温度读取函数 带1位小数位
float floatReadDs18B20(void) 
{



















}