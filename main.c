#include<p18f4520.h>
#define RS PORTCbits.RC1 
#define RW PORTCbits.RC0 
#define EN PORTCbits.RC2 
#define dataline PORTD
#define r0 PORTBbits.RB5
#define r1 PORTBbits.RB6
#define r2 PORTBbits.RB7
#define c0 PORTBbits.RB1
#define c1 PORTBbits.RB2
#define c2 PORTBbits.RB3
#define c3 PORTBbits.RB4
void lcd_init(void);
void lcd_string(unsigned char *p);
void lcd_cmd(unsigned char c);
void lcd_data (unsigned char d);
void delay(int);
void UART_init(void);
void trans(unsigned char);
unsigned char receive(void);

void main(){
int pass[4];
unsigned char x,id[12];
unsigned char  id1[13]="09001F5E89C1";
unsigned char  wel[15]="Welcome  ";
unsigned char scan[15]="Scan  Card";

unsigned char acc2[15]="Enter Password";
unsigned char acc3[15]="Access Granted";
unsigned char acc4[10]="Denid";
int i;

 TRISB=0x1E;

INTCON2bits.RBPU=0;
ADCON1=0x0f;
TRISC = 0x80 ;
lcd_init();
UART_init();
  while(1)
{  
  lcd_cmd(0x80);
  lcd_string(wel);
  lcd_cmd(0xC0);
  lcd_string(scan); 
for(i=0;i<12;i++)
{
 x=receive();
trans(x);
id[i]=x;
}
if(id[0]==id1[0]&&id[1]==id1[1]&&id[2]==id1[2]&&id[3]==id1[3]&&id[4]==id1[4]&&id[5]==id1[5]&&id[6]==id1[6]&&id[7]==id1[7]&&id[8]==id1[8]&&id[9]==id1[9]&&id[10]==id1[10]&&id[11]==id1[11])
{
lcd_cmd(0x01);
lcd_cmd(0xc0);
lcd_string(acc2);

delay(500);

i=0;
while(i<4)
{
	 
    	r0=0;
		r1=r2=1;
		if(c0==0)
		{
			lcd_data('1');
            pass[i]=1;
			i++;
		}
	  	r0=0;
		r1=r2=1;
		if(c1==0)
		{
			lcd_data('2');
			pass[i]=2;
			i++;
		}
		
	
		r0=0;
		r1=r2=1;
		if(c2==0)
		{
			lcd_data('3');
				pass[i]=3;
			i++;
		}
     	r0=0;
		r1=r2=1;
        if(c3==0)
          {
             lcd_data('4');
           	pass[i]=4;
			i++;
	     }
		r1=0;
		r0=r2=1;
		if(c0==0)
		{
			lcd_data('5');
				pass[i]=5;
			i++;
		}
			r1=0;
		r0=r2=1;
		if(c1==0)
		{
			lcd_data('6');
				pass[i]=6;
			i++;
		}
		r1=0;
		r0=r2=1;
		if(c2==0)
		{
			lcd_data('7');
				pass[i]=7;
			i++;
		}

    	r1=0;
		r0=r2=1;
		if(c3==0)
		{
			lcd_data('8');
			pass[i]=8;
			i++;
		}
		r2=0;
		r0=r1=1;
		if(c0==0)
		{
			lcd_data('9');
				pass[i]=9;
			i++;
		}
	
		
		r2=0;
		r0=r1==1;
		if(c1==0)
		{
			lcd_data('0');
				pass[i]=0;
			i++;
		}
     	delay(200);
  }     
	 if((pass[0]==1)&&(pass[1]==2)&&(pass[2]==3)&&(pass[3]==4))
	 {
		 lcd_cmd(0x01);
		 lcd_cmd(0x80);
		 lcd_string(acc3);
		 delay(5000);
	 }
	 else 
	 {
		  lcd_cmd(0x01);
		  lcd_cmd(0x80);
		 lcd_string(acc4);
		 delay(5000); 
	 }
     
}
     else 
    {
         lcd_cmd(0x01);
		 lcd_cmd(0x80);
		 lcd_string(acc4);
		 delay(5000); 
     }
}
}	
void lcd_init()
{
  TRISD=0x00;
  TRISC=0x00;
lcd_cmd(0x30);
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x0f);
	lcd_cmd(0x80);

}
void UART_init(void){
TRISC=0x80;
TXSTA=0x24;
RCSTA=0x90;
SPBRG=0x81;
}
void trans(unsigned char x){
 TXREG=x;
 while(TXSTAbits.TRMT==0);
}
unsigned char receive(){
 while(PIR1bits.RCIF==0);
return RCREG;
}

void lcd_data(unsigned char d)
{
	dataline=d;
	RS=1;
	RW=0;
	EN=1;
	delay(10);
	EN=0;
	delay(10);
}
void lcd_cmd(unsigned char c)
{
	dataline=c;
	RS=0;
	RW=0;
	EN=1;
	delay(10);
	EN=0;
	delay(10);
}
void delay(int t)
{
int i ,j ;
for( i=0;i<t;i++)
for( j=0;j<498;j++);
}
void lcd_string(unsigned char *p)
{ 
	int i;
	for(i=0;p[i]!='\0';i++)
	{
		lcd_data(p[i]);
	}
}