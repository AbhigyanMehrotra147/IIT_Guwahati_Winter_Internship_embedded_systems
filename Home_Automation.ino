#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int fan = 10;
int LED = 11;
int inByte;
unsigned char cmd;

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(fan,OUTPUT);
  digitalWrite(fan,LOW);
  digitalWrite(LED,LOW);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Home Automation");
  lcd.setCursor(0,1);
  delay(1000);
  Serial.begin(9600);
}


void loop()
{
  if (Serial.available() > 0)
  {
    inByte = Serial.read();
    switch(inByte)
    {
      case 'a':
        digitalWrite(fan,HIGH);
        lcd.setCursor(0,1);
        lcd.print("   Fan ON   ");
        break;
      case 'b':
        digitalWrite(fan,LOW);
        lcd.setCursor(0,1);
        lcd.print("   Fan OFF   ");
        break;
       case 'c':
        digitalWrite(LED,HIGH);
        lcd.setCursor(0,0);
        lcd.print("   Light ON   ");
        break;
       case 'd':
        digitalWrite(LED,LOW);
        lcd.setCursor(0,0);
        lcd.print("   Light OFF   ");
        break;      
    }
  }
}
