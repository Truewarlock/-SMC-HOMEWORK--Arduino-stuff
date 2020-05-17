#include <LiquidCrystal.h>
#define ADC_VREF_TYPE ((0<<REFS1)|(0<<REFS0)|(0<<ADLAR))

LiquidCrystal lcd(12,13,11,10,9,8);

float stepADC=0.0048828125;

void setup()
{
  lcd.begin(2,16);
  initializareADC();
}

void loop()
{
  lcd.print("Val:");
  unsigned int sensorValue=citesteADC(0);
  float val =stepADC*sensorValue;
  lcd.print(val,2);
  lcd.setCursor(0,1);
  lcd.print("Stare:");
  if(val<=2.45)
  {lcd.print("Safe");}
  if((val>2.45)&&(val<4))
  {lcd.print("Riscant");}
  if(val>=4)
  {lcd.print("Hazard");}

  delay(500);
  lcd.clear();
 
  
 
}


unsigned int citesteADC(unsigned char adc_input)
{
  ADMUX=adc_input |ADC_VREF_TYPE;
  delayMicroseconds(10);
  
  ADCSRA|=(1<<ADSC);
  while((ADCSRA&(1<<ADIF))==0){}
  ADCSRA |=(1<<ADIF);
  
  return ADCW;
  
  
}

void initializareADC()
{
  DIDR0=(0<<ADC5D)|(0<<ADC4D)|(0<<ADC3D)|(0<<ADC2D)|(0<<ADC1D)|(0<<ADC0D);
  ADMUX=ADC_VREF_TYPE;
  
  ADCSRA=(1<<ADEN)|(0<<ADSC)|(1<<ADATE)|(0<<ADIF)|(0<<ADIE)|(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);
}


















  