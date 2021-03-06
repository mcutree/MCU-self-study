/*-----------------------------------------------
  名称：8*8点阵
  修改：无
  内容：点阵上显示数字0
------------------------------------------------*/

#include<reg52.h>	            //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#define  uint unsigned int   
#define  uchar  unsigned char   

sbit  DZL = P2^1;               //573的列锁存
sbit  DZH = P2^0;               //573的行锁存

uchar  dx_table1[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};	 //列数据选择
uchar  dx_table2[]={0x00,0x00,0x3e,0x41,0x41,0x41,0x3e,0x00};	 //行数据选择
 
 /************延时函数**************/
void delay(void)
{
	uchar i,j;                  //定义两个无符号字符型
	for(i=0;i<30;i++)
		for(j=0;j<20;j++);
}

/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main()
{
 	uchar i;
	while(1)
	{
		for(i=0;i<8;i++)		//8*8点阵的每行每列都要选择8次
		{
			P1=dx_table1[i];	//列选择
			DZL=1;				//数据锁存
			DZL=0;
	
			P1=dx_table2[i];	//行选择
			DZH=1;				//数据锁存
			DZH=0;
			delay();
		}
	}		
}