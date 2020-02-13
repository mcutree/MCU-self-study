/*-----------------------------------------------
  名称：矩阵键盘中断扫描
  微信公众号：电子开发之家
  编写：小树	
  版本：Version 1.0
  内容：使用行列扫描方法  		
        中断方式可以有效提供cpu工作效率，在有按键动作时才扫描，平时不进行扫描工作
------------------------------------------------*/


#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#define KeyPort  P0
sbit dula=P2^1;
sbit wela=P2^0;

unsigned char code  DuanMa[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
		                  	         0x77,0x7c,0x39,0x5e,0x79,0x71};// 显示段码值0~F
unsigned char num; 

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
	dula=1;
	P1=0xff;
	dula=0;
	wela=1;
	P1=0x00;
	wela=0;                 


	EA=1;          //全局中断开
	EX0=1;         //外部中断0开
	IT0=1;         //边沿触发

while (1)         //主循环
  {
	display(num);
	KeyPort=0xf0;// 赋值用于中断检测		
 }
}

void display(unsigned char aa)
{
	dula=1;
	P1=DuanMa[aa];
	dula=0;		
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


/*------------------------------------------------
按键扫描函数，返回扫描键值
------------------------------------------------*/
unsigned char KeyScan(void)  //键盘扫描函数，使用行列逐级扫描法
{
 unsigned char Val;
 KeyPort=0xf0;//高四位置高，低四位拉低
 if(KeyPort!=0xf0)//表示有按键按下
   {
    DelayMs(10);  //去抖
	if(KeyPort!=0xf0)
	  {           //表示有按键按下
    	KeyPort=0xfe; //检测第一行
		if(KeyPort!=0xfe)
	  		{
			  Val=KeyPort&0xf0;
	  	      Val+=0x0e;
	  		  while(KeyPort!=0xfe);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xfe);
	     	  return Val;
	        }
        KeyPort=0xfd; //检测第二行
		if(KeyPort!=0xfd)
	  		{
			  Val=KeyPort&0xf0;
	  	      Val+=0x0d;
	  		  while(KeyPort!=0xfd);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xfd);
	     	  return Val;
	        }
    	KeyPort=0xfb; //检测第三行
		if(KeyPort!=0xfb)
	  		{
			  Val=KeyPort&0xf0;
	  	      Val+=0x0b;
	  		  while(KeyPort!=0xfb);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xfb);
	     	  return Val;
	        }
    	KeyPort=0xf7; //检测第四行
		if(KeyPort!=0xf7)
	  		{
			  Val=KeyPort&0xf0;
	  	      Val+=0x07;
	  		  while(KeyPort!=0xf7);
			  DelayMs(10); //去抖
			  while(KeyPort!=0xf7);
	     	  return Val;
	        }
     }
   }
  return 0xff;
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
                 外部中断0程序
------------------------------------------------*/
void ISR_INT0(void) interrupt 0 
{ 
	num=KeyPro();  
	IE0=0;
}
