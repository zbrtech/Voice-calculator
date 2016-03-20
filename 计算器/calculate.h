#include<string.h>
#include<math.h>
#define  uchar unsigned char 
#define  uint  unsigned int
/********************************1602*************/
void wait();
void write_dat(unsigned char dat);
void lcd_l602init();
void write_cmd(unsigned char cmd);
void write_dat(unsigned char dat);
/***************转换函数*************/
void dis_res(double res);//小数转字符
double stod(char *s);//字符转小数
void play_result();
/**********************************/
void PlaySoundTick(uchar  number);
void  spi_pu (void);
void  spi_stop (void);
void isd1700_Npar_comm (uchar comm_par,comm_byte_count);
void GetSound(uchar soundtick);
void GetSound(uchar soundtick);
void delay(int x);
void delay_isd(uint time);
uchar T_R_comm_byte( uchar comm_data );
/**********************************************/
