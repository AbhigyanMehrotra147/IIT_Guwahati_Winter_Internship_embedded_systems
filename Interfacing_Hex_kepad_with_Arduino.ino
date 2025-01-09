#include <LiquidCrystal.h>
LiquidCrystal lcd(0,1,2,3,4,5);

//// Defining the row pins
int row_1 = 6;
int row_2 = 7;
int row_3 = 8;
int row_4 = 9;

//// Defining the column pins
int col_1 = 10;
int col_2 = 11;
int col_3 = 12;
int col_4 = 13;






void setup() 
{
  //// The row pins are outputs 
  pinMode(row_1,OUTPUT);
  pinMode(row_2,OUTPUT);
  pinMode(row_3,OUTPUT);
  pinMode(row_4,OUTPUT);

  //// The column pins are inputs
  pinMode(col_1,INPUT);
  pinMode(col_2,INPUT);
  pinMode(col_3,INPUT);
  pinMode(col_4,INPUT);      

  //// Initially setting all column pins as HIGH
  digitalWrite(col_1,HIGH);
  digitalWrite(col_2,HIGH);
  digitalWrite(col_3,HIGH);
  digitalWrite(col_4,HIGH);

  lcd.begin(16,2); //// Initializing LCD
  lcd.setCursor(0,0);
  lcd.print(" Hex Keypad  ");
  delay(1000);
  lcd.clear();
}

void loop() 
{
  //// ****************************Detection for first row************************************
  digitalWrite(row_1,LOW);
  digitalWrite(row_2,HIGH);
  digitalWrite(row_3,HIGH);
  digitalWrite(row_4,HIGH);

  if(digitalRead(col_1) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("1");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("2");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("3");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("A");
    delay(200);
  }
  //// *********************************Detection second row*********************************************************
  digitalWrite(row_1,HIGH);
  digitalWrite(row_2,LOW);
  digitalWrite(row_3,HIGH);
  digitalWrite(row_4,HIGH);

  if(digitalRead(col_1) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("4");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("5");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("6");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("B");
    delay(200);
  }
  //// ******************************************Detection for third row*********************************************
  digitalWrite(row_1,HIGH);
  digitalWrite(row_2,HIGH);
  digitalWrite(row_3,LOW);
  digitalWrite(row_4,HIGH);

  if(digitalRead(col_1) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("7");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("8");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("9");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("C");
    delay(200);
  }
  //// **************************************Detection for fourth row*******************************
  digitalWrite(row_1,HIGH);
  digitalWrite(row_2,HIGH);
  digitalWrite(row_3,HIGH);
  digitalWrite(row_4,LOW);

  if(digitalRead(col_1) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("*");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("0");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("+");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    lcd.setCursor(7,1);
    lcd.print("D");
    delay(200);
  }
}
