#include<LiquidCrystal.h>
#include<Keypad.h>
#define RANDURI 4
#define COLOANE 4

const int rs=12,en=13,d4=11,d5=10,d6=9,d7=8;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
char valoareTasta[RANDURI][COLOANE] = 
{
{'1','2','3','+'},
{'4','5','6','-'},
{'7','8','9','*'} , 
{'R','0','#','/'}
};

byte piniRanduri [RANDURI] = {7,6,5,4};
byte piniColoane [COLOANE] = {3,2,1,0};

Keypad tastatura(
makeKeymap(valoareTasta),
piniRanduri,
piniColoane,
RANDURI,COLOANE);

void setup()
{
  DDRD=0x00;
  lcd.begin(16,2);
  
  
}
int auxnumar1;
int auxnumar2;
char auxoperand='0';
int numar1;
int numar2;
char operand='0';
float rez;

void show()
{
  lcd.setCursor(0,0);
  lcd.print(numar1);
  if(operand!='0')
  {lcd.print(operand);
   lcd.print(numar2);
  	
  }
  
  
}
void calcRez()
{
  if(operand=='+')
  {rez=numar1+numar2;}
  if(operand=='-')
  {rez=numar1-numar2;}
  if(operand=='*')
  {rez=numar1*numar2;}
  if(operand=='/')
  {rez=numar1/numar2;}
}

int caracter(char a)
{
  if((a=='0')|(a=='1')|(a=='2')|(a=='3')|
     (a=='4')|(a=='5')|(a=='6')|(a=='7')|
     (a=='8')|(a=='9'))
  {
    if(auxoperand=='0')
    { 	
      auxnumar1=(auxnumar1)*10+(int)a - 48;
      numar1=auxnumar1;
      
       
     show();
  
    }
    else
    {
      auxnumar2=(auxnumar2)*10+(int)a - 48;
      numar2=auxnumar2;
      
      show();
    }
  }
  if(a=='R')
  { 
    auxnumar1=0;
    auxnumar2=0;
    numar1=0;
    numar2=0;
    operand='0';
    lcd.setCursor(0,0);
  	lcd.print("                                          ");
  	lcd.setCursor(0,1);
  	lcd.print("                                          ");
    show();
    
  }
  if(a=='#')
  {	calcRez();
    lcd.setCursor(0,1);
  	lcd.print("=");
  	lcd.print(rez);
  }
  if((a=='+')|(a=='-')|(a=='*')|(a=='/'))
  {
    auxoperand=a;
    operand=auxoperand;
    show();
  }
}
void loop()
{
  const char tastaApasata=tastatura.getKey();
  if(tastaApasata !=0)
  {
    caracter(tastaApasata);
    
  }
  
 
}