#include<calculate.h>
#include<reg52.h>
/*sbit RS=P2^6;    //寄存器选择位，将RS位定义为P2.0引脚
sbit RW=P2^5;    //读写选择位，将RW位定义为P2.1引脚
sbit EN=P2^7;     //使能信号位，将E位定义为P2.2引脚	*/
sbit BUSY=P0^7;
sbit RS=P2^0;    //寄存器选择位，将RS位定义为P2.0引脚
sbit RW=P2^1;    //读写选择位，将RW位定义为P2.1引脚
sbit EN=P2^2;     //使能信号位，将E位定义为P2.2引脚
    //忙碌标志位，，将BF位定义为P0.7引脚 */
extern char key; 
void wait()//读状态和读数据（等待是不是忙)	 											
{
	P0=0xff;
	do
	{
		RS=0;
		RW=1;
		EN=0;
		EN=1;
	}while(BUSY==1);
	EN=0;

}
void write_dat(unsigned char dat)//1602写数据
{
  	wait();
    RS=1;
   	RW=0;
	EN=1;
	P0=dat;
	EN=0;
}
void write_cmd(unsigned char cmd)//1602写命令
{
	wait();
	RS=0;
	RW=0;
    EN=1;
	P0=cmd;
	EN=0;
    
				 
}
void lcd_l602init()//1602初始化
{
	EN=0;
	write_cmd(0x38);//设置16*2显示	
	write_cmd(0x0c);//显示器开，光标开
	write_cmd(0x06);//写一个字符后地址加1
	write_cmd(0x01);//显示清0,DPTR清0

}
 