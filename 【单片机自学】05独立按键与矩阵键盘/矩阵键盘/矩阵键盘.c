/*-----------------------------------------------
  名称：矩阵键盘反转扫描
  微信公众号：电子开发之家
  编写：小树
  版本：Version 1.0
  内容：矩阵键盘反转扫描
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

#define KeyPort P3
sbit dula=P2^1;
sbit wela=P2^0;
unsigned char code DuanMa[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void DelayUs2x(unsigned char t);//us级延时函数声明 
void DelayMs(unsigned char t); //ms级延时

unsigned char KeyScan(void);//键盘扫描
unsigned char KeyPro(void);
void display(unsigned char aa);
/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main (void)
{
unsigned char num;   
	dula=1;
	P1=0x00;
	dula=0;
	wela=1;
	P1=0x00;
	wela=0;       
while (1)         //主循环
	{
		num=KeyPro();
	if(num!=0xff)
   {
		display(num);
	}
}
}
void display(unsigned char aa)
{
	dula=1;
	P1=DuanMa[aa];
	dula=0;		
}
/*------------------------------------------------
          按键扫描函数，返回扫描键值
------------------------------------------------*/
unsigned char KeyScan(void)  //键盘扫描函数，使用行列反转扫描法
{
	unsigned char cord_h,cord_l;//行列值中间变量
	KeyPort=0x0f;            //列线输出全为0
	cord_h=KeyPort&0x0f;     //读入行线值
	if(cord_h!=0x0f)    //先检测有无按键按下
	{
		DelayMs(10);        //去抖
		if((KeyPort&0x0f)!=0x0f)
	{
    cord_h=KeyPort&0x0f;  //读入行线值
    KeyPort=cord_h|0xf0;  //输出当前列线值
    cord_l=KeyPort&0xf0;  //读入列线值

    while((KeyPort&0xf0)!=0xf0);//等待松开并输出
    return(cord_h+cord_l);//键盘最后组合码值
   }
  }return(0xff);     //返回该值
}
/*------------------------------------------------
              按键值处理函数，返回扫键值
------------------------------------------------*/
unsigned char KeyPro(void)
{
 switch(KeyScan())
 {
  case 0x7e:return 0;break;//0 按下相应的键显示相对应的码值
  case 0x7d:return 1;break;//1
  case 0x7b:return 2;break;//2
  case 0x77:return 3;break;//3
  case 0xbe:return 4;break;//4
  case 0xbd:return 5;break;//5
  case 0xbb:return 6;break;//6
  case 0xb7:return 7;break;//7
  case 0xde:return 8;break;//8
  case 0xdd:return 9;break;//9
  case 0xdb:return 10;break;//a
  case 0xd7:return 11;break;//b
  case 0xee:return 12;break;//c
  case 0xed:return 13;break;//d
  case 0xeb:return 14;break;//e
  case 0xe7:return 15;break;//f
  default:return 0xff;break;
 }
}
/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
