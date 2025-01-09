int IN1 = 4;
int IN2 = 5;

int IN3 = 6;
int IN4 = 7;


void setup() 
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);

  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  Serial.begin(9600);
}




void loop()
{
  
  if(Serial.available())
  {
    unsigned char inByte = Serial.read();
    switch(inByte)
    {
      case 'F':{move_forward();}break;
      case 'B':{move_backward();}break;
      case 'L':{move_left();}break;
      case 'R':{move_right();}break;
      case 'S':{stop_car();}break;
    }
  }
}

void move_forward()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void move_backward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void move_left()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void move_right()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void stop_car()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
