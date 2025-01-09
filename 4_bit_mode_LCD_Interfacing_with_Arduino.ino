#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
void setup()
{
  lcd.begin(16,2);
}

void loop() 
{
  lcd.setCursor(0,0);
  lcd.print("    Welcome     "); 
  lcd.setCursor(0,1);
  lcd.print("  To Arduino  ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Hello   "); 
  lcd.setCursor(0,1);
  lcd.print("   Abhigyan   ");
  delay(1000);
  lcd.clear();
}
