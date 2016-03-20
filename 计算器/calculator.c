#include<calculate.h>
#include<reg52.h>
#define  uchar unsigned char 
#define  uint  unsigned int

char astring[8];//�����洢a
char bstring[8];//�����洢b	
bit acomp=0; //Ϊ�ڶ�����������ǰ����������
bit ecomp=0;//Ϊ��ʾ���ǰ���������
char symbol=-1;//�����������Ƿ�����
double a=0,b=0,c=0;//�洢�����������������ͽ�� 
char astring[8];//�����洢a��ÿһλ
char bstring[8];//�����洢b��ÿһλ	
char key=-1;//���ڴ�Ű�����ֵ	

unsigned char code digit[]={'1','2','3','4',
			  '5','6','7','8',
			  '9','+','-','*',
			  '/','=','0','.',};
unsigned char code key_code[]={
              0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d, 
              0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};	//���̵ı���
void delay1ms(int n)//n������ʱ																	
{
	int i,j;
   for(i=n;i>0;i--)
   for(j=120;j>0;j--);//12M  ����11.0592M����115
}
char  keyscan()
{
   char  scan1,scan2,keycode,j;
   P1=0xf0;
   scan1=P1;
   if((scan1&0xf0)!=0xf0)           //�м��Ƿ���
   {
     delay1ms(20);                   //��ʱ20ms
     scan1=P1;
     if((scan1&0xf0)!=0xf0)         //�����м��Ƿ���
     {
        P1=0x0f;  //�߷�ת���ĺ���
        scan2=P1;
        keycode=scan1|scan2;         //��ϳɼ�����
        for(j=0;j<=15;j++)
        {
           if(keycode== key_code[j])  //���ü�ֵ
           {
              key=j;
			  //while(!P1);
              return(key);
           }
        } 
     }
   }
 
}
void time_init()
{
	TMOD=0X01;
	TH0=(65536-10000)/256;
	TL0=(65536-10000)/256;//20MS
	EA=1;
	ET0=1;
	TR0=1;
}
 void delayhg(int n)
{
	int i=100;
	while(n--)
	{
		i--;
	}
}
void calculate()
{
	switch(symbol)
	{
		case '+':
		c=a+b;
		break;
		case '-':
		c=a-b;
		break;
		case '*':
		c=a*b;
		break;
		case '/':
		c=a/b;
	
		break;
	}	
}
void chushihua()
{
	char i=0;
	key=-1;
    symbol=-1;
	lcd_l602init();
	for(i=0;i<8;i++)
	{
		astring[i]=0;
		bstring[i]=0;	
	}
}

void main()
{  
		
	char i=0;  //�������ڶ������ݴ洢ʱ���ѭ������
	char t=0; //��������һ�����ݴ洢ʱ���ѭ������
    lcd_l602init();
	time_init();
	spi_pu();
    lcd_l602init();
    while(1)
	{
		if(key!=-1)
		{
			
			if(symbol==-1&&((key>=0&&key<=8)||(key>=14&&key<=15)))//���a
			{
	          	write_dat(digit[key]);
				PlaySoundTick(key);
				delay1ms(5);
			    astring[i++]=digit[key];
				key=-1;//����keyΪ��Ч
			}
			else if(symbol==-1&&key>=9&&key<=12)//������*/
			{
				 symbol=digit[key];//���︳ֵ���ǡ�+-*/���������case���Ӧ�ú��������Ӧ
				 write_dat(digit[key]);
				 PlaySoundTick(key);
				 delay1ms(5);
				 key=-1;
        		 a=stod(astring);//����a��ת��
				 acomp=1;
			}
			else if(symbol!=-1&&((key>=0&&key<=8)||(key>=14&&key<=15)))//���b//symbol ���������ᱻ��λ�����ڵ���-1������Ӧ����else if
			{
				if(acomp==1)
				{
					write_cmd(0x80+0x40);
					acomp=0;
				}
	          	write_dat(digit[key]);
			  	PlaySoundTick(key);
				delay1ms(5);
			  bstring[t++]=digit[key];
			  key=-1;//����keyΪ��Ч
			  ecomp=1;
			}
			else if(symbol!=-1&&key==13)//��⡰=��
			{
			    EA=0;
			    ET0=0;
			    TR0=0; 
			  if(ecomp==1)
			  {
			  	write_cmd(0x01);
				ecomp=0;
			  }
	    	  write_dat(digit[key]);
			  PlaySoundTick(key);
			  b=stod(bstring);//����b��ת��
			  calculate();
			  dis_res(c);
			  key=-1;
			  /*EA=1;
			  ET0=1;
			  TR0=1;*/
		    }
			 						
          }	 
	} 
}
void T0_time()interrupt 1
{
	TH0=(65536-10000)/256;
	TL0=(65536-10000)/256;//20MS
	keyscan();
	

}

/*// �����ʱ������С�������׼���⣬�������� 
	
	char s1[8]="12.5";
	char s2[8]="10.0";
	a=stod(s1);
	b=stod(s2);
	c=a+b;
    lcd_l602init();
	time_init();
	 dis_res(c);
     while(1)
	{
	   
	} 
  */

























	


