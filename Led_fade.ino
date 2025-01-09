int led = 11;
void setup() 
{
  pinMode(led,OUTPUT);
}

void loop() 
{
  for(int brightness = 255; brightness >= 0; brightness -= 5)
  {
    analogWrite(led,brightness);
    delay(100);
  }
}
