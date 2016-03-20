#include<calculate.h>
#include<reg52.h>
#define  uchar unsigned char 
#define  uint  unsigned int

char astring[8];//用来存储a
char bstring[8];//用来存储b	
bit acomp=0; //为第二个数据输入前换行做检验
bit ecomp=0;//为显示结果前清屏做检测
char symbol=-1;//检测运算符号是否输入
double a=0,b=0,c=0;//存储操作数两个运算数和结果 
char astring[8];//用来存储a的每一位
char bstring[8];//用来存储b的每一位	
char key=-1;//用于存放按键的值	

unsigned char code digit[]={'1','2','3','4',
			  '5','6','7','8',
			  '9','+','-','*',
			  '/','=','0','.',};
unsigned char code key_code[]={
              0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d, 
              0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};	//键盘的编码
void delay1ms(int n)//n毫秒延时																	
{
	int i,j;
   for(i=n;i>0;i--)
   for(j=120;j>0;j--);//12M  若是11.0592M则是115
}
char  keyscan()
{
   char  scan1,scan2,keycode,j;
   P1=0xf0;
   scan1=P1;
   if((scan1&0xf0)!=0xf0)           //判键是否按下
   {
     delay1ms(20);                   //延时20ms
     scan1=P1;
     if((scan1&0xf0)!=0xf0)         //二次判键是否按下
     {
        P1=0x0f;  //线反转法的核心
        scan2=P1;
        keycode=scan1|scan2;         //组合成键编码
        for(j=0;j<=15;j++)
        {
           if(keycode== key_code[j])  //查表得键值
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
		
	char i=0;  //用来做第二个数据存储时候的循环变量
	char t=0; //用来做第一个数据存储时候的循环变量
    lcd_l602init();
	time_init();
	spi_pu();
    lcd_l602init();
    while(1)
	{
		if(key!=-1)
		{
			
			if(symbol==-1&&((key>=0&&key<=8)||(key>=14&&key<=15)))//检测a
			{
	          	write_dat(digit[key]);
				PlaySoundTick(key);
				delay1ms(5);
			    astring[i++]=digit[key];
				key=-1;//设置key为无效
			}
			else if(symbol==-1&&key>=9&&key<=12)//检测符号*/
			{
				 symbol=digit[key];//这里赋值的是‘+-*/’，下面的case语句应该和这里相对应
				 write_dat(digit[key]);
				 PlaySoundTick(key);
				 delay1ms(5);
				 key=-1;
        		 a=stod(astring);//进行a的转换
				 acomp=1;
			}
			else if(symbol!=-1&&((key>=0&&key<=8)||(key>=14&&key<=15)))//检测b//symbol 经过上面后会被置位，不在等于-1，所以应该用else if
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
			  key=-1;//设置key为无效
			  ecomp=1;
			}
			else if(symbol!=-1&&key==13)//检测“=”
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
			  b=stod(bstring);//进行b的转换
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

/*// 计算的时候必须加小数点否则不准问题，函数不当 
	
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

























	


