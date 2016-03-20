#include<calculate.h>
#include<reg52.h>
/*sbit RS=P2^6;    //�Ĵ���ѡ��λ����RSλ����ΪP2.0����
sbit RW=P2^5;    //��дѡ��λ����RWλ����ΪP2.1����
sbit EN=P2^7;     //ʹ���ź�λ����Eλ����ΪP2.2����	*/
sbit BUSY=P0^7;
sbit RS=P2^0;    //�Ĵ���ѡ��λ����RSλ����ΪP2.0����
sbit RW=P2^1;    //��дѡ��λ����RWλ����ΪP2.1����
sbit EN=P2^2;     //ʹ���ź�λ����Eλ����ΪP2.2����
    //æµ��־λ������BFλ����ΪP0.7���� */
extern char key; 
void wait()//��״̬�Ͷ����ݣ��ȴ��ǲ���æ)	 											
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
void write_dat(unsigned char dat)//1602д����
{
  	wait();
    RS=1;
   	RW=0;
	EN=1;
	P0=dat;
	EN=0;
}
void write_cmd(unsigned char cmd)//1602д����
{
	wait();
	RS=0;
	RW=0;
    EN=1;
	P0=cmd;
	EN=0;
    
				 
}
void lcd_l602init()//1602��ʼ��
{
	EN=0;
	write_cmd(0x38);//����16*2��ʾ	
	write_cmd(0x0c);//��ʾ��������꿪
	write_cmd(0x06);//дһ���ַ����ַ��1
	write_cmd(0x01);//��ʾ��0,DPTR��0

}
 