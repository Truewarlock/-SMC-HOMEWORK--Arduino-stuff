#include <avr/interrupt.h>
#define pA 0
#define pB 1
#define pC 4
#define pD 5
#define pE 6
#define pF 7
#define pG 0

int counter=0;

ISR(INT0_vect)
{
  SREG &=~(1<<SREG_I);
  
  counter++;
  
  
  SREG |=1<<SREG_I;
}

ISR(INT1_vect)
{
  SREG &=~(1<<SREG_I);
  
  counter--;
  
  SREG |=1<<SREG_I;
}

void setup()
{
  DDRD=B11111111;
  //DDRD=(1<<pA)|(1<<pB)|(1<<pC)|(1<<pD)|(1<<pE)|(1<<pF);
  DDRB=(1<<pG);
  //PORTD=(1<<pA)|(1<<pB)|(1<<pC)|(1<<pD)|(1<<pE)|(1<<pF);
  

  
 
  
  //interrupt
  SREG |=(1<<SREG_I);
  
  
  
EICRA |=(1<<ISC11)|(1<<ISC10)|(1<<ISC01)|(1<<ISC00);
EIMSK |=(1<<INT1)|(1<<INT0);
EIFR |=(0<<INTF1)|(0<<INTF0);
PCICR |=(0<<PCIE2)|(0<<PCIE1)|(0<<PCIE0);
  
}

const char a[10]=
{
1,0,1,1,0,1,1,1,1,1
};
const char b[10]=
{
1,1,1,1,1,0,0,1,1,1
};
const char c[10]=
{
1,1,0,1,1,1,1,1,1,1
};
const char d[10]=
{
1,0,1,1,0,1,1,0,1,1
};
const char e[10]=
{
1,0,1,0,0,0,1,0,1,0
};
const char f[10]=
{
1,0,0,0,1,1,1,0,1,1
};
const char g[10]=
{
0,0,1,1,1,1,1,0,1,1
};


void loop()
{
  if (counter>9){counter=9;}
  if (counter<0){counter=0;}
  PORTD=(a[counter]<<pA)|(b[counter]<<pB)|(c[counter]<<pC)
    |(d[counter]<<pD)|(e[counter]<<pE)|(f[counter]<<pF);
  PORTB=(g[counter]<<pG);
 
  if((PINB&(1<<PIN1))==0)
  {
    while((PINB&(1<<PIN1))==0)
    {}
    counter=0;
  }
   
}