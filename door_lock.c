#include<reg51.h>
#include<string.h>
#define LCDdata P2
sbit LCDrs=P1^0;
sbit LCDrw=P1^1;
sbit LCDen=P1^2;
sbit m1=P1^3;
sbit m2=P1^4;
const char pass[]="12345";
char num[4];
int i;
sbit col1=P3^6;
sbit col2=P3^5;
sbit col3=P3^4;
sbit row1=P3^3;
sbit row2=P3^2;
sbit row3=P3^1;
sbit row4=P3^0;
void delay(unsigned int rtime)
{
	unsigned int r,s;
	for(r=0;r<rtime;r++)
	for(s=0;s<1275;s++);
}
void lcd_cmd(unsigned char DATA)
{
	LCDrs=0;
	LCDrw=0;
	LCDen=1;
	LCDdata=DATA;
	LCDen=0;
}
void lcd_data(unsigned int DATA)
{
	LCDrs=1;
	LCDrw=0;
	LCDen=1;
	LCDdata=DATA;
	LCDen=0;
}
void initialize(void)
{
	lcd_cmd(0x30);       //1 line 5*7 matrix
	delay(1);
	lcd_cmd(0x38);       //2 line 5*7 matrix
	delay(1);
	lcd_cmd(0x0c);       // display on cursor off
	delay(1);
	lcd_cmd(0x01);       //clear display screem
	delay(1);
	lcd_cmd(0x10);       //shift curspr to right
	delay(1);
}
void display_string(unsigned char *d)
{
	while(*d)
	{
		lcd_data(*d++);
		delay(1);
  }
}
void check_col1(int i)
{
	row1=row2=row3=row4=1;
	row1=0;
	if(col1==0)
		num[i]='1';
	
	row1=1;
	row2=0;
	if(col1==0)
		num[i]='4';

	row2=1;
	row3=0;
	if(col1==0)
		num[i]='7';
	
	row3=1;
	row4=0;
	if(col1==0)
		num[i]='*';
	
	row4=1;
	
}
void check_col2(int i)
{
	row1=row2=row3=row4=1;
	row1=0;
	if(col2==0)
		num[i]='2';
	
	row1=1;
	row2=0;
	if(col2==0)
		num[i]='5';
	
	row2=1;
	row3=0;
	if(col2==0)
		num[i]='8';
	
	row3=1;
	row4=0;
	if(col2==0)
		num[i]='0';
	
	row4=1;
}
void check_col3(int i)
{
	row1=row2=row3=row4=1;
	row1=0;
	if(col3==0)
		num[i]='3';
	
	row1=1;
	row2=0;
	if(col3==0)
		num[i]='6';
	
	row2=1;
	row3=0;
	if(col3==0)
		num[i]='9';
	
	row3=1;
	row4=0;
	if(col3==0)
		num[i]='#';
	
	row4=1;
}
void keypad()
{
	while(i<5)
	{
		
		row1=row2=row3=row4=0;
		if(col1==0)
		{
			
			
			display_string("*");
			
			check_col1(i);
			delay(100);
			i++;
		}
		else if(col2==0)
		{
			
			delay(1);
			
			display_string("*");
			check_col2(i);
			delay(100);
			i++;
		}
		else if(col3==0)
		{
			
			delay(1);
			display_string("*");
			check_col3(i);
			delay(100);
			i++;
		}
	}
}
void main()
{
	unsigned int x=0;
	initialize();
	lcd_cmd(0x80);
	delay(1);
	display_string("Door Locked");
	
	col1=col2=col3=1;	//input port
	lcd_cmd(0xc0);
	keypad();
	
	
	if(pass[0]==num[0] && pass[1]==num[1] && pass[2]==num[2] && pass[3]==num[3] && pass[4]==num[4])
	{
		
		lcd_cmd(0x80);
		delay(1);
		display_string("Door unlocked");
		delay(100);
		m1=0;
		m2=1;
		
	}
	else
	{
		lcd_cmd(0xc0);
		delay(1);
		display_string("wrong password");
		delay(100);
	}
	while(1);
}

