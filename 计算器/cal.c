#include<calculate.h>
double code pows[]={0.000001,  0.00001,  0.0001 ,  0.001,
				0.01 ,   0.1,       1,       10,   
				100,    1000,     10000,    100000,
				1000000,10000000,100000000,1000000000,
				10000000000};
extern char code digit[];
extern void delay1ms(int n);


void dis_res(double res)//С��ת�ַ�,�����˸�����ʾ���ܣ�������û��С����С�����ֲ���ʾ��
{ 
	char s[20];
	char nega_flag=-1;
	char notallzero_flag=-1;
	int num1;
	size_t i=0;
	int t=0;
	long int_part=0;
	long float_part=0;

	if(res<0)
	{
		res=fabs(res);
		nega_flag=1;
	}
	int_part=(long)res; 
	float_part=(long)((res-(float)int_part)*1000000);//
	while(1)
	{
		if(int_part>=pows[i+6])
		{
			i++;
		}
		else
		{
			break;
		}
	}
	num1=i;//num1=i-1;//�洢�������ֵ�λ��
	for(i=1;i<=num1;i++)
	{
		s[i-1]=(char)(int_part/(long)pows[6+num1-i])+'0';
		int_part=int_part%(long)pows[6+num1-i];
	}
	s[i-1]='.';//�洢С����
	for(t=1;t<=6;t++)//С�������ʾ��λ��
	{
		s[i-1+t]=(char)(float_part/(long)pows[12-t])+'0';
		float_part=float_part%(long)pows[12-t];
		if(s[i-1+t]!='0')//�ַ����ַ���ȵ�ƥ�䣬���������Ǻ� 0��ƥ����
		{	
			notallzero_flag=1;
		}
	}
	s[i-1+t]='\0';
	if(nega_flag==1)
	{
		write_dat('-');
		PlaySoundTick(10);
		delay1ms(1000);
	}
	if(notallzero_flag==1)
	{
		for(i=0;i<strlen(s);i++)
		{
			write_dat(s[i]);
			switch (s[i])
			{
				case '0':
				PlaySoundTick(14);
				break;
				case '1':
				PlaySoundTick(0);
				break;
				case '2':
				PlaySoundTick(1);
				break;
				case '3':
				PlaySoundTick(2);
				break;
				case '4':
				PlaySoundTick(3);
				break;
				case '5':
				PlaySoundTick(4);
				break;
				case '6':
				PlaySoundTick(5);
				break;
				case '7':
				PlaySoundTick(6);
				break;
				case '8':
				PlaySoundTick(7);
				break;
				case '9':
				PlaySoundTick(8);
				break;
				case '.':
				PlaySoundTick(15);
				break;
			}
			delay1ms(1000);
				
		}
	}
	else
	{
		for(i=1;i<=num1;i++)
		{
			write_dat(s[i-1]);
			switch (s[i-1])
			{
				case '0':
				PlaySoundTick(14);
				break;
				case '1':
				PlaySoundTick(0);
				break;
				case '2':
				PlaySoundTick(1);
				break;
				case '3':
				PlaySoundTick(2);
				break;
				case '4':
				PlaySoundTick(3);
				break;
				case '5':
				PlaySoundTick(4);
				break;
				case '6':
				PlaySoundTick(5);
				break;
				case '7':
				PlaySoundTick(6);
				break;
				case '8':
				PlaySoundTick(7);
				break;
				case '9':
				PlaySoundTick(8);
				break;
				case '.':
				PlaySoundTick(15);
				break;
			
			}
			delay1ms(1000);
		}
	}
}
double stod(char *s)
{ 
	char len=0,i=0;int dot=-1;//�洢С�����λ��
	double Val=0;
  	len=strlen(s)-1;//len������Կ������������Ԫ�ص��±�
	for(i=0;i<=len;i++)
	{
		if(s[i]=='.')
		{	
		   dot=i;
		   i=0;
		   break;
		 }
		 
	}
	if(dot!=-1)//��⵽С����
	{	
		for(i=0;i<dot;i++)
		{
			Val+=(double)(s[i]-'0')*pows[dot-i-1+6];
		}
		i++;
		for(;i<=len;i++)
		{
			Val+=(double)(s[i]-'0')*pows[6+dot-i];
		}
	}
	else //�������û��С����
	{
		for(i=0;i<=len;i++)
		{
			Val+=(double)(s[i]-'0')*pows[len-i-1+7];//���ﵱ����Ϊpow����仯 �����±�Ҫ�ı�
		}
	}
	return Val;
}
/*void play_result()
{
	int i=0;
	int find_temp=0;
	if(nega_flag==1)
	{
		PlaySoundTick(10);
	}
	if(notallzero_flag==1)
	{
		for(i=0;i<strlen(s);i++)
		{
			switch (s[i])
			{
				case '0':
				PlaySoundTick(14);
				break;
				case '1':
				PlaySoundTick(0);
				break;
				case '2':
				PlaySoundTick(1);
				break;
				case '3':
				PlaySoundTick(2);
				break;
				case '4':
				PlaySoundTick(3);
				break;
				case '5':
				PlaySoundTick(4);
				break;
				case '6':
				PlaySoundTick(5);
				break;
				case '7':
				PlaySoundTick(6);
				break;
				case '8':
				PlaySoundTick(7);
				break;
				case '9':
				PlaySoundTick(8);
				break;
				case '.':
				PlaySoundTick(15);
			
			}
				delay1ms(500);
		}
	}
	else
	{
		for(i=1;i<=num1;i++)
		{
			switch (s[i-1])
			{
				case '0':
				PlaySoundTick(14);
				break;
				case '1':
				PlaySoundTick(0);
				break;
				case '2':
				PlaySoundTick(1);
				break;
				case '3':
				PlaySoundTick(2);
				break;
				case '4':
				PlaySoundTick(3);
				break;
				case '5':
				PlaySoundTick(4);
				break;
				case '6':
				PlaySoundTick(5);
				break;
				case '7':
				PlaySoundTick(6);
				break;
				case '8':
				PlaySoundTick(7);
				break;
				case '9':
				PlaySoundTick(8);
				case '.':
				PlaySoundTick(15);
			
			}
				delay1ms(500);
		
	 
		}
	}
}*/


