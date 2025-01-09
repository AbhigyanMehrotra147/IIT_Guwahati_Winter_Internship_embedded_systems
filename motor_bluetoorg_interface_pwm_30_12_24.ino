int IN1 = 4;
int IN2 = 5;

int IN3 = 6;
int IN4 = 7;

int enable1 = 11;
int enable2 = 10;

void setup() 
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);

  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(enable1,OUTPUT);
  pinMode(enable2,OUTPUT);
  
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
    control_speed(inByte);
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

void control_speed(int pwm_value)
{
  switch(pwm_value)
  {
    case '9':
    {
      analogWrite(enable1,255);
      analogWrite(enable2,255);
    } break;
    case '8':
    {
      analogWrite(enable1,225);
      analogWrite(enable2,225);
    } break;
    case '1':
    {
      analogWrite(enable1,50);
      analogWrite(enable2,50);
    } break;
    case '2':
    {
      analogWrite(enable1,75);
      analogWrite(enable2,75);
    } break;
    case '3':
    {
      analogWrite(enable1,100);
      analogWrite(enable2,100);
    } break;
    case '4':
    {
      analogWrite(enable1,125);
      analogWrite(enable2,125);
    } break;
    case '5':
    {
      analogWrite(enable1,150);
      analogWrite(enable2,150);
    } break;
    case '6':
    {
      analogWrite(enable1,175);
      analogWrite(enable2,175);
    } break;
    case '7':
    {
      analogWrite(enable1,200);
      analogWrite(enable2,200);
    } break;
    case '0':
    {
      analogWrite(enable1,0);
      analogWrite(enable2,0);
    } break;
  }
}

void stop_car()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
