#include<LiquidCrystal.h>

 
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

//// Defining which key is what
char keys[4][6] =
{
  {'_', '7', '8', '9', '*', '/'},
  {'_', '4', '5', '6', '-', '_'},
  {'%', '1', '2', '3', '+', '_'},
  {'s', '0', '.', '=', '+', '_'}
};

//// row pins are outputs
struct row
{
  int one = 22;
  int two = 23;
  int three = 24;
  int four = 25;
};

//// column pins are inputs;
struct column
{
  int one = 26;
  int two = 27;
  int three = 28;
  int four = 29;
  int five = 30;
  int six = 31;
};

String input = ""; //// string to store input from user
struct row Row;
struct column Column;
bool valid; //// flag, whether expression is valid or not
float Operand_1;
float Operand_2;
char Operator;
float result; ////  to store result
bool is_infinity; //// infinity flag

//// function to define and initialize pins
void init_pins()
{
  pinMode(Row.one, OUTPUT);
  pinMode(Row.two, OUTPUT);
  pinMode(Row.three, OUTPUT);
  pinMode(Row.four, OUTPUT);

  pinMode(Column.one, INPUT);
  pinMode(Column.two, INPUT);
  pinMode(Column.three, INPUT);
  pinMode(Column.four, INPUT);
  pinMode(Column.five, INPUT);
  pinMode(Column.six, INPUT);

  //// initalizing all column pins as high
  digitalWrite(Column.one, HIGH);
  digitalWrite(Column.two, HIGH);
  digitalWrite(Column.three, HIGH);
  digitalWrite(Column.four, HIGH);
  digitalWrite(Column.five, HIGH);
  digitalWrite(Column.six, HIGH);
}
//// initialize lcd

void init_lcd()
{
  lcd.begin(16, 2); //// Initializing LCD
  lcd.setCursor(0, 0);
  lcd.print("Lets Calculate");
  delay(2000);
  lcd.clear();
}

void setup()
{
  init_pins();
  init_lcd();
}

//// function to control which row is low
void control_rows(int low_row)
{
  digitalWrite(Row.one, HIGH);
  digitalWrite(Row.two, HIGH);
  digitalWrite(Row.three, HIGH);
  digitalWrite(Row.four, HIGH);
  if (low_row == 1)
  {
    digitalWrite(Row.one, LOW);
  }
  else if (low_row == 2)
  {
    digitalWrite(Row.two, LOW);
  }
  else if (low_row == 3)
  {
    digitalWrite(Row.three, LOW);
  }
  else
  {
    digitalWrite(Row.four, LOW);
  }
}
//// Function reads a single row
void read_row(int row)
{
  control_rows(row);
  if (digitalRead(Column.one) == LOW)
  {
    input.concat(keys[row - 1][0]);
    //// if the user wants to clear the screen
    if (row == 1)
    {
      input = "";
      lcd.clear();
    }
    delay(200);
  }
  else if (digitalRead(Column.two) == LOW)
  {
    input.concat(keys[row - 1][1]);
    delay(200);
  }
  else if (digitalRead(Column.three) == LOW)
  {
    input.concat(keys[row - 1][2]);
    delay(200);
  }
  else if (digitalRead(Column.four) == LOW)
  {
    input.concat(keys[row - 1][3]);
    delay(200);
  }
  else if (digitalRead(Column.five) == LOW)
  {
    input.concat(keys[row - 1][4]);
    delay(200);
  }
  else if (digitalRead(Column.six) == LOW)
  {
    input.concat(keys[row - 1][5]);
    delay(200);
  }
}

//// function reads any key pressed on the computer
void read_key()
{
  read_row(1);
  read_row(2);
  read_row(3);
  read_row(4);
  read_row(5);
  read_row(6);
}
//// Function to display what the input provider has typed.
void display_question()
{
  lcd.setCursor(0, 0);
  lcd.print(input);
  delay(10);
}

//// checks if expression is valid
bool check_validity()
{
  lcd.setCursor(0, 0);
  for (int i = 0; i < input.length(); i += 1)
  {
    if (input[i] == '_')
    {
      lcd.print("Invalid EXP");
      input = "";
      delay(1000);
      lcd.clear();
      return 0;
    }
  }
  
//  lcd.print("Valid EXP");
//  delay(1000);
  return 1;
}

//// Function parses the expression into operands and operation
void parse_expression()
{
  if(input[0] == 's')
  {
    Operand_1 = input.substring(1).toFloat();
    Operator = 's';
    input = "";
    return;
  }
  for(int i = 0;i<input.length()-1;i+=1)
  {
    if(input[i]=='+' || input[i]=='-' || input[i]=='/'||
      input[i]=='%'||input[i]=='*')
      {
        Operator = input[i];
        Operand_1 = input.substring(0,i).toFloat();
        Operand_2 = input.substring(i+1).toFloat();
      }
      
  }
  input = "";
}
//// performs computation
float compute()
{
  switch(Operator)
  {
    case 's':
      {
        return sqrt(Operand_1);
      }
    case '+':
      {
        return Operand_1 + Operand_2;
      }
    case '-':
      {
        return Operand_1 - Operand_2;
      }
    case '/':
      {
       if(Operand_2 == 0) 
       {
          is_infinity = 1;
          break;
       }
       return Operand_1/Operand_2;
      }
    case '*':
      { 
        return Operand_1*Operand_2;
      }
    case '%':
      {
          return (int)Operand_1 % (int)Operand_2;
      }
  }
}
void print_result()
{
  lcd.clear();
  lcd.setCursor(0,0);
  if(is_infinity)
  {
    lcd.print("infinity");
  }
  else
  {
    lcd.print(result);
  }
  delay(1000);
  lcd.clear(); 
}
void loop()
{
  //// to read the express
  read_key();
  display_question();
  if(input[input.length()-1] == '=')
  {
    valid = check_validity();
    if(valid)
    {
      parse_expression();
      result = compute();
      print_result();
    }
  }
  
}
