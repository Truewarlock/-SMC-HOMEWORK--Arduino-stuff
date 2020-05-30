#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#include <LiquidCrystal.h>

byte Buffer[4];
LiquidCrystal lcd(12,13,11,10,9,8);

//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_Print(char* StringPtr);

char String1[]="";    



unsigned char c = 0;
int counter;
bool clear=false;




int main(void){
lcd.begin(16,2);
USART_init(); 
int y=0;
//lcd.print("Temp:");
//lcd.setCursor(12,0);
//lcd.print("C");
while(1){ 
  
  	lcd.setCursor(y,0);
    USART_receive();
  	USART_Print(String1);
	
  	
	if(lcd.print(String1))
    {y++;}
  	if(y>7){y=0;}
  
  	
  	
  	
 

  
}

return 0;
}

void USART_init(void){

UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
UBRR0L = (uint8_t)(BAUD_PRESCALLER);
UCSR0B = (1<<RXEN0)|(1<<TXEN0)| (1<<RXCIE0);
UCSR0C = ((1<<UCPOL0) | (1<<UCSZ01) | (1<<UCSZ00));
}

unsigned char USART_receive(void){
int i = 0;
while(!(UCSR0A & (1<<RXC0)));
    String1[i] = UDR0;
    i++;
  	
return UDR0;
  

}

void USART_send( unsigned char data){

while(!(UCSR0A & (1<<UDRE0)));
UDR0 = data;

}

void USART_Print(char* StringPtr){
 while(*StringPtr != 0x00){
   USART_send(*StringPtr);
   StringPtr++;
 }
}	