/*-----------------------------------------------
  ���ƣ�������̷�תɨ��
  ΢�Ź��ںţ����ӿ���֮��
  ��д��С��
  �汾��Version 1.0
  ���ݣ�������̷�תɨ��
------------------------------------------------*/
#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���

#define KeyPort P3
sbit dula=P2^1;
sbit wela=P2^0;
unsigned char code DuanMa[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void DelayUs2x(unsigned char t);//us����ʱ�������� 
void DelayMs(unsigned char t); //ms����ʱ

unsigned char KeyScan(void);//����ɨ��
unsigned char KeyPro(void);
void display(unsigned char aa);
/*------------------------------------------------
                    ������
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
while (1)         //��ѭ��
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
          ����ɨ�躯��������ɨ���ֵ
------------------------------------------------*/
unsigned char KeyScan(void)  //����ɨ�躯����ʹ�����з�תɨ�跨
{
	unsigned char cord_h,cord_l;//����ֵ�м����
	KeyPort=0x0f;            //�������ȫΪ0
	cord_h=KeyPort&0x0f;     //��������ֵ
	if(cord_h!=0x0f)    //�ȼ�����ް�������
	{
		DelayMs(10);        //ȥ��
		if((KeyPort&0x0f)!=0x0f)
	{
    cord_h=KeyPort&0x0f;  //��������ֵ
    KeyPort=cord_h|0xf0;  //�����ǰ����ֵ
    cord_l=KeyPort&0xf0;  //��������ֵ

    while((KeyPort&0xf0)!=0xf0);//�ȴ��ɿ������
    return(cord_h+cord_l);//������������ֵ
   }
  }return(0xff);     //���ظ�ֵ
}
/*------------------------------------------------
              ����ֵ������������ɨ��ֵ
------------------------------------------------*/
unsigned char KeyPro(void)
{
 switch(KeyScan())
 {
  case 0x7e:return 0;break;//0 ������Ӧ�ļ���ʾ���Ӧ����ֵ
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
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{     
 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
