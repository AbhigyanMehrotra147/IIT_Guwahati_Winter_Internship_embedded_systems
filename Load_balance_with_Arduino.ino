#include <LiquidCrystal.h>
LiquidCrystal(2,3,4,5,6,7);
int PIR = 12;
int count = 0;
int Status = 0;
int buzzer = 0'

void setup() 
{

  pinMode(PIR,INPUT);
  pinMode(PIR,OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Visitor Counter")
  lcd.setCursor(0,1);
  lcd.print("   Device   ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("No of ");
  lcd.setCursor(0,1);
  lcd.print("Visitors:  ");
  lcd.setCursor(9,1);
  lcd.print(count);
  
}

void loop() 
{

}
