#include <Servo.h>
Servo myservo;
byte pwmvalue = 0;
int pos = 0;
void setup()
{
  myservo.attach(9);
//}
1
void loop() 
{
  myservo.write(pwmvalue);
  delay(15);
  pwmvalue++;
}
