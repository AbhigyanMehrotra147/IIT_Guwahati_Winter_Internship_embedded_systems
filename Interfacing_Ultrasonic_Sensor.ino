#include <LiquidCrystal.h> 
LiquidCrystal lcd(2,3,4,5,6,7);
const int trigPin = 9;
const int echoPin = 10;
long duration; // For some reason long is chosen by the instructor
int distanceCm;
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Hello");
  delay(2000);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() 
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  duration = pulseIn(echoPin,HIGH); // a predefined function gives the time for which the echo pin was high
  distanceCm = duration*0.034/2; // distance in cm/microsec
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distanceCm);
  lcd.print(" cm");
  delay(10);
}
