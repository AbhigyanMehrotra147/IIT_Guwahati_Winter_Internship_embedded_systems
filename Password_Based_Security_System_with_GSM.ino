#include <LiquidCrystal.h>
LiquidCrystal lcd(A0,A1,2,3,4,5);

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

//// Defining other variables:
int password = 0; //// For storing the password entered by incomer
int temp = 0; //// temporary varable
int pos = 0; //// tells if the digit is 1000th, 100th, 10th or unit position
int state = 0;
int led = A3;
int alarm = A2;
int PIN=1234; //// the actual password


void send_sms()
{
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"9555755802"");
  delay(1000);
}

void setup() 
{
  //// alarm and led
  pinMode(led,OUTPUT);
  pinMode(alarm,OUTPUT);

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
  lcd.print("Security System");
  delay(1000);
  lcd.clear();

  lcd.print("Enter PIN");
  delay(1000);
  lcd.clear();
}

void get_password(int digit)
{
  pos+=1;
  lcd.clear();
  if(pos == 1)
  {
    password += digit*1000;
  }
  else if(pos == 2)
  {
    password += digit*100;
  }
  else if(pos == 3)
  {
    password += digit*10;
  }
  else
  {
    lcd.clear();
    password += digit;
    if (password == PIN)
    {
      digitalWrite(led,HIGH);
      digitalWrite(alarm,LOW);
      lcd.setCursor(0,1);
      lcd.print("Opened");
      pos = 0;
      password = 0;
    }
    else
    {
      if(state == 1)
      {
        digitalWrite(led,LOW);
        digitalWrite(alarm,HIGH);
        lcd.setCursor(0,1);
        lcd.print("Wrong_password");
        pos = 0;
        password = 0;
        state = 0
      }
      else
      {
        digitalWrite(led,LOW);
        digitalWrite(alarm,HIGH);
        lcd.setCursor(0,1);
        lcd.print("Wrong_password");
        pos = 0;
        password = 0;
        send_sms();
      }
    }
  }
  
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
    get_password(1);
    lcd.setCursor(7,1);
    lcd.print("1");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    get_password(2);
    lcd.setCursor(7,1);
    lcd.print("2");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    get_password(3);
    lcd.setCursor(7,1);
    lcd.print("3");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    get_password(10);
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
    get_password(4);
    lcd.setCursor(7,1);
    lcd.print("4");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    get_password(5);
    lcd.setCursor(7,1);
    lcd.print("5");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    get_password(6);
    lcd.setCursor(7,1);
    lcd.print("6");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    get_password(11);
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
  
  { get_password(7);
    lcd.setCursor(7,1);
    lcd.print("7");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    get_password(8);
    lcd.setCursor(7,1);
    lcd.print("8");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    get_password(9);
    lcd.setCursor(7,1);
    lcd.print("9");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    get_password(12);
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
    get_password(13);
    lcd.setCursor(7,1);
    lcd.print("D");
    delay(200);
  }
  else if(digitalRead(col_2) == LOW)
  {
    get_password(14);
    lcd.setCursor(7,1);
    lcd.print("E");
    delay(200);
  }
  else if(digitalRead(col_3) == LOW)
  {
    get_password(15);
    lcd.setCursor(7,1);
    lcd.print("F");
    delay(200);
  }
  else if(digitalRead(col_4) == LOW)
  {
    get_password(0);
    lcd.setCursor(7,1);
    lcd.print("0");
    delay(200);
  }
}
