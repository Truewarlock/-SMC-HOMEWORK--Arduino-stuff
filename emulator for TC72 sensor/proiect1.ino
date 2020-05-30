#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1




void USART_Init(unsigned int ubrr)
{
  UBRR0H=(unsigned char)(ubrr>>8);
  UBRR0L=(unsigned char)ubrr;
  UCSR0B=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C=(1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
  while(!(UCSR0A&(1<<UDRE0)));
  UDR0=data;
  
}

void SendString(char *StringPtr)
{
  while(*StringPtr !=0x00)
  {
    USART_Transmit(*StringPtr);
    StringPtr++;
  }
}


void setup()
{	//serial
	USART_Init(MYUBRR);
 
}


float val=12.34;

void convertire()
{int aux=val*100;
  if (aux<-5500){aux=-5500;};
  if(aux>12500){aux=12500;};
 
  char semn='+';
  if(aux<0)
  {aux=aux*(-1);
  semn='-';}
  
 int i4=aux%10; 
  aux=aux/10;
  
 int i3=aux%10;
  aux=aux/10;
  
 int i2=aux%10;
  aux=aux/10;
  
 int i1=aux%10;
  aux=aux/10;
 int i0=aux%10;
  
 char c0=i0+'0'; 
 char c1=i1+'0';
 char c2=i2+'0';
 char c3=i3+'0';
 char c4=i4+'0';
 USART_Transmit(semn);
 USART_Transmit(c0);
 USART_Transmit(c1);
 USART_Transmit(c2);
 USART_Transmit('.');
 USART_Transmit(c3);
 USART_Transmit(c4);
 USART_Transmit('C');
 
}
void loop()
{ 
	if((PINB&(1<<PIN0))==0)
  {
    while((PINB&(1<<PIN0))==0)
    {}
    val=val+0.01;
    convertire();
    
  }
  if((PINB&(1<<PIN1))==0)
  {
    while((PINB&(1<<PIN1))==0)
    {}
    val=val+0.5;
    convertire();
    
  }
  if((PINB&(1<<PIN2))==0)
  {
    while((PINB&(1<<PIN2))==0)
    {}
    val=val+10;
    convertire();
    
  }
  if((PINB&(1<<PIN3))==0)
  {
    while((PINB&(1<<PIN3))==0)
    {}
    val=val-0.01;
    convertire();
    
  }
  if((PINB&(1<<PIN4))==0)
  {
    while((PINB&(1<<PIN4))==0)
    {}
    val=val-0.5;
    convertire();
    
  }
  if((PINB&(1<<PIN5))==0)
  {
    while((PINB&(1<<PIN5))==0)
    {}
    val=val-10;
    convertire();

  }
  


  
}