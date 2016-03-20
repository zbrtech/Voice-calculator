#include<reg51.h>
#define uchar unsigned char 
#define uint unsigned int
sbit ISD_SS=P0^7;
sbit ISD_MISO=P0^4;
sbit ISD_MOSI=P0^5;
sbit ISD_SCLK=P0^6; 
#define ISD1700_PU          0x01
#define ISD1700_STOP        0X02
#define ISD1700_REST        0x03
#define ISD1700_CLR_INT     0x04
#define ISD1700_RD_STAUS    0x05
#define ISD1700_RD_PLAY_PTR 0x06
#define ISD1700_PD          0x07
#define ISD1700_RD_REC_PTR  0x08
#define ISD1700_DEVID       0x09

#define ISD1700_PLAY        0x40
#define ISD1700_REC         0x41
#define ISD1700_ERASE       0x42
#define ISD1700_G_ERASE     0x43
#define ISD1700_RD_APC      0x44
#define ISD1700_WR_APC1     0x45
#define ISD1700_WR_APC2     0x65

#define ISD1700_WR_NVCFG    0x46
#define ISD1700_LD_NVCFG    0x47
#define ISD1700_FWD         0x48
#define ISD1700_CHK_MEM     0x49
#define ISD1700_EXTCLK      0x4A
#define ISD1700_SET_PLAY    0x80
#define ISD1700_SET_REC     0x81
#define ISD1700_SET_ERASE   0x82
#define NULL                0x00
#define ISD_LED             0x10

#define sound_1A           0x0010 
#define sound_1B           0x0016

#define sound_2A           0x0017 
#define sound_2B           0x001C

#define sound_3A           0x001D  
#define sound_3B           0x0023

#define sound_4A           0x0024  
#define sound_4B           0x002B

#define sound_5A           0x002C  
#define sound_5B           0x0032

#define sound_6A           0x0033 
#define sound_6B           0x0039

#define sound_7A           0x003A  
#define sound_7B           0x0041

#define sound_8A           0x0042 
#define sound_8B           0x0049

#define sound_9A           0x004A 
#define sound_9B           0x0051

#define sound_10A          0x0052  //»¶Ó­À´·Ã£¬ÇëÊäÈë·¿ºÅ¡£
#define sound_10B          0x0059

#define sound_11A          0x005A  //ÕýÔÚºô½Ð£¬ÇëÉÔºò¡£
#define sound_11B          0x0060

#define sound_12A          0x0061  //ÕýÔÚºô½Ð£¬ÇëÉÔºò¡£
#define sound_12B          0x0067

#define sound_13A          0x0068  
#define sound_13B          0x006D

#define sound_14A          0x006E  
#define sound_14B          0x0074

#define sound_15A          0x0075  
#define sound_15B          0x007A

#define sound_16A          0x007B  
#define sound_16B          0x0081

#define sound_17A          0x0082  
#define sound_17B          0x0010
unsigned char data ISD_COMM_RAM[7];
uchar data *isd_comm_ptr;
void delay(int x)
{  
	     uchar i;
		 for(; x>=1; x--)
		  {for(;i<=20;i++);}
}
void delay_isd(uint time)
{
	while(time--!=0);
}
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
         //rest_isd_comm_ptr();
		 isd_comm_ptr=ISD_COMM_RAM;		 
         i=0;
         do{
             //*back_data_ptr++=T_R_comm_byte(*isd_comm_ptr++);
             //i++;
			 T_R_comm_byte(*isd_comm_ptr++);
             i++;
           }while(i<=7);
       }
void GetSound(uchar soundtick)
{
	ISD_SS=0;
	switch(soundtick)
	{  
		
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
	    default: break;
     }
	ISD_SS=1;
}
void isd1700_Npar_comm (uchar comm_par,comm_byte_count)
       {   
	     uchar i;
		 i=0;
		 ISD_COMM_RAM[0]=comm_par;
		 isd_comm_ptr=&ISD_COMM_RAM[1];
		 do{ 
		     *isd_comm_ptr++=NULL;
		    }while(++i<comm_byte_count-1);

		 //rest_isd_comm_ptr();	
		 isd_comm_ptr=ISD_COMM_RAM;	 
         i=0;
         do{
             //*back_data_ptr++=T_R_comm_byte(*isd_comm_ptr++);
			 T_R_comm_byte(*isd_comm_ptr++);
             i++;
           }while(i<comm_byte_count);
	    }
void  spi_stop (void)
      {  
		 ISD_SS=0;
         isd1700_Npar_comm(ISD1700_STOP,2);     
		 ISD_SS=1;
      }
void  spi_pu (void)
      {  
		 ISD_SS=0;
         isd1700_Npar_comm(ISD1700_PU,2);    
		 ISD_SS=1;
      }
void PlaySoundTick(uchar  number)
{
	  spi_stop ();
	  delay_isd(3000);
      GetSound(number);
}
void main()
{
	int i;
	spi_pu();
	while(1)
	{
	
	for(i=1;i<11;i++)
	{
		PlaySoundTick(i);
		if(i==12)
		{
			i=0;
		}
	}
	}
}	

   


	