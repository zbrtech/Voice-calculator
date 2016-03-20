#include"reg51.h"
#include "sound.h"
#include "ISD1700.H"
#define uchar unsigned char 
#define uint unsigned int
sbit ISD_SS=P2^4;
sbit ISD_MISO=P2^7;
sbit ISD_MOSI=P2^6;
sbit ISD_SCLK=P2^5;
/*sbit ISD_SS=P3^3;
sbit ISD_MISO=P3^0;
sbit ISD_MOSI=P3^1;
sbit ISD_SCLK=P3^2;	*/
/*sbit ISD_SS=P2^7;
sbit ISD_MISO=P2^4;
sbit ISD_MOSI=P2^5;
sbit ISD_SCLK=P2^6;*/
void PlaySoundTick(uchar soundtick);
uchar data  comm_temp;
uchar data  ISD_COMM_RAM[7];
uchar data  ISD_COMM_RAM_C[7];
uchar data  *isd_comm_ptr;
uchar data  *back_data_ptr;

// 函数声明
void  delay(int x);
void  comm_sate(void);
void  rest_isd_comm_ptr(void);
uchar T_R_comm_byte( uchar comm_data );
void isd1700_Npar_comm(uchar comm_par,comm_byte_count); //no parameter comm
void isd1700_par2_comm(uchar comm_par, uint data_par);
void isd1700_7byte_comm(uchar comm_par, uint star_addr, uint end_addr);

void  spi_pu(void);
void  spi_stop(void);
void  spi_Rest( void );
void  spi_RD_play_ptr(void);
void  spi_RD_rec_ptr(void);
void  spi_devid(void);
void  spi_play(void);
void  spi_rec(void);
void  spi_erase(void);
void  spi_G_ERASE(void);
void  spi_fwd(void);
void  spi_wr_apc2(void);
void  spi_CurrRowAddr(void);

void  seril_back_sate(uchar byte_number);
void  spi_set_opt(uchar spi_set_comm);


// 上位机通信接口函数


			  
// 芯片上电
void spi_pu(void)
{  
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_PU,2);    
	ISD_SS=1;
}

// 停止当前
void spi_stop (void)
{  
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_STOP,2);     
	ISD_SS=1;
 	ISD_COMM_RAM_C[0]=ISD1700_STOP ;
   	seril_back_sate(1);
}

// 芯片复位
void spi_Rest(void)
{
	ISD_SS=0;
  	isd1700_Npar_comm(ISD1700_REST,2);    
	ISD_SS=1;
}

// 当前地址
void  spi_CurrRowAddr(void)
{    
	uchar i;
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_RD_STAUS,3); 
	ISD_SS=1;
	i=ISD_COMM_RAM_C[1];
	ISD_COMM_RAM_C[1]=ISD_COMM_RAM_C[0]>>5|ISD_COMM_RAM_C[1]<<3;  
	ISD_COMM_RAM_C[0]= i >>5;   
	seril_back_sate(3);
}

// 读播放地址
void spi_RD_play_ptr(void)
{    
	uchar i;
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_RD_PLAY_PTR,4);      
	ISD_SS=1;			
	i=ISD_COMM_RAM_C[3]&0x03;               
	ISD_COMM_RAM_C[3]=ISD_COMM_RAM_C[2];    
	ISD_COMM_RAM_C[2]=i;
	seril_back_sate(4);
}

// 读录音地址
void  spi_RD_rec_ptr(void)
{    
	uchar i;
	ISD_SS=0;
 	isd1700_Npar_comm(ISD1700_RD_REC_PTR,4);      
	ISD_SS=1;
	i=ISD_COMM_RAM_C[3]&0x03;                 
	ISD_COMM_RAM_C[3]=ISD_COMM_RAM_C[2]; 
	ISD_COMM_RAM_C[2]=i;
	seril_back_sate(4);
}

// 读器件ID
void spi_devid(void)
{
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_DEVID,3);   
	ISD_SS=1;
	ISD_COMM_RAM_C[2]=ISD_COMM_RAM_C[2]&0xf8; 
	seril_back_sate(3);
}

// 播放当前语音
void  spi_play(void)
{   
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_PLAY|ISD_LED,2);    
	ISD_SS=1;
}

// 录音函数
void spi_rec (void)
{
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_REC|ISD_LED,2);      
	ISD_SS=1;
	ISD_COMM_RAM_C[0]=ISD1700_REC ;
	seril_back_sate(1);
}
// 擦除当前
void spi_erase (void)
{
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_ERASE|ISD_LED,2);      
	ISD_SS=1;
}
// 擦除全部
void spi_G_ERASE (void) 
{ 
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_G_ERASE|ISD_LED,2);    
	ISD_SS=1;
}
// 下一段语音
void spi_fwd (void)
{
	ISD_SS=0;
	isd1700_Npar_comm(ISD1700_FWD,2);      
	ISD_SS=1;
}

// 写APC寄存器
void  spi_wr_apc2(void)
{
	ISD_SS=0;
	isd1700_par2_comm(ISD1700_WR_APC2, 0x0400);
	ISD_SS=1;
}

// 串口返回函数
void seril_back_sate(uchar byte_number)
{
	uchar sate_temp;
	rest_isd_comm_ptr();
	sate_temp=0;
	do{
		SBUF=*back_data_ptr++;
		while(!TI);
		TI=0;
	  }while(++sate_temp<byte_number);
}

// 指针复位
void rest_isd_comm_ptr(void)
{
	isd_comm_ptr=ISD_COMM_RAM;
	back_data_ptr=ISD_COMM_RAM_C; 
}

// 发送命令
void isd1700_Npar_comm (uchar comm_par,comm_byte_count)
{   
	uchar i;
	i=0;
	ISD_COMM_RAM[0]=comm_par;
	isd_comm_ptr=&ISD_COMM_RAM[1];
	do{ 
	*isd_comm_ptr++=NULL;
	}while(++i<comm_byte_count-1);

	rest_isd_comm_ptr();		 
	i=0;
	do{
	*back_data_ptr++=T_R_comm_byte(*isd_comm_ptr++);
	i++;
	}while(i<comm_byte_count);
}

// 发送命令2
void isd1700_par2_comm(uchar comm_par, uint data_par)
{
	uchar i;
	ISD_COMM_RAM[0]=comm_par;
	ISD_COMM_RAM[1]=data_par;
	ISD_COMM_RAM[2]=data_par>>8;         
	rest_isd_comm_ptr();		 
    i=0;
    do{
		*back_data_ptr++=T_R_comm_byte(*isd_comm_ptr++);
		i++;
	  }while(i<3);
}

// 发送7个字节
void isd1700_7byte_comm(uchar comm_par, uint star_addr, uint end_addr)
{
	uchar i;
	ISD_COMM_RAM[0]=comm_par;
	ISD_COMM_RAM[1]=NULL;
	ISD_COMM_RAM[2]=star_addr;
	ISD_COMM_RAM[3]=star_addr>>8;
	ISD_COMM_RAM[4]=end_addr;
	ISD_COMM_RAM[5]=end_addr>>8;
	ISD_COMM_RAM[6]=NULL;
	rest_isd_comm_ptr();		 
	i=0;
	do{
		*back_data_ptr++=T_R_comm_byte(*isd_comm_ptr++);
		i++;
	  }while(i<=7);
}

// SPI通信函数
uchar T_R_comm_byte( uchar comm_data )
{
	uchar bit_nuber;
	uchar temp;
	bit_nuber=0;
	temp=0;
	do{
	ISD_SCLK=0;
	delay(1);
	if((comm_data>>bit_nuber&0x01)!=0) 
	{ISD_MOSI=1;}
	else
	{ISD_MOSI=0;}
	if(ISD_MISO)
	{temp=(temp>>1)|0x80;}
	else
	{temp=temp>>1;}
	ISD_SCLK=1;
	delay(1);
			 
	}while(++bit_nuber<=7);
	ISD_MOSI=0;
	return (temp);
}

// 短延时
void delay(int x)
{  
	uchar i;
	for(; x>=1; x--)
	{for(;i<=20;i++);}
}

// 播放指定语音段函数
void PlaySoundTick(char soundtick)
{
	ISD_SS=0;
	switch(soundtick)
	{  
		case 0:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_0A, sound_0B); }break;
		case 1:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_1A, sound_1B); }break;
	    case 2:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_2A, sound_2B); }break;
	    case 3:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_3A, sound_3B); }break;
	    case 4:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_4A, sound_4B); }break;
	    case 5:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_5A, sound_5B); }break;
	    case 6:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_6A, sound_6B); }break;
		case 7:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_7A, sound_7B); }break;
		case 8:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_8A, sound_8B); }break;
	    case 9:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_9A, sound_9B); }break;
	    case 10:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_10A, sound_10B); }break;
	    case 11:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_11A, sound_11B); }break;
	    case 12:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_12A, sound_12B); }break;
	    case 13:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_13A, sound_13B); }break;
		case 14:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_14A, sound_14B); }break;
	    case 15:{ isd1700_7byte_comm(ISD1700_SET_PLAY|ISD_LED, sound_15A, sound_15B); }break;
		/*
		任意添加语音段，语音段始末地址（用上位机读出）填在SOUND.H文件中
		*/
	    default: break;
     }
	ISD_SS=1;
}