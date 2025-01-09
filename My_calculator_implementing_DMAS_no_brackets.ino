#include <LiquidCrystal.h>
#define DEBOUNCE_DELAY 200 //// setting debounce delay as 200 milliseconds
LiquidCrystal lcd(0,1,2,3,4,5);

//// creating a struct which can hold the operator and its precedence
struct Operator_precedence 
{
  char Operator;
  int precedence;
};

//// table to store all operator and precedence
Operator_precedence table[] = 
{
  {'/',3},
  {'*',3},
  {'-',2},
  {'+',1},
};

const int ROWS = 4;
const int COLUMNS = 4;

//// Declaring the key structure
char keys[ROWS][COLUMNS]
{
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'_','0','=','+'}
};

//// Declaring the Row and Column pins on arduino
int row_pins[ROWS] = {6,7,8,9};
int col_pins[COLUMNS] = {13,12,11,10};

//// Varaibles:
String input = "";
bool valid_exp = false; //// flag to declare that expression is valid
float result; //// variable to store the result of the operation

char* operand_token; ////charcter pointer to store operand_token
char* operator_token; //// character pointer to store operator token
const char* operator_delimiters = "/*-+="; //// defining the delimiters for operands as tokens
const char* operand_delimiters = "0123456789="; //// defining the delimiters for operators as tokens


//// function to check validity of the expression
void check_validity()
{
  valid_exp = true;
}

//// defining operations
float operations(float operand_1, float operand_2, char Operator)
{ 
  if(Operator == '+') return operand_1 + operand_2;
  else if(Operator == '-') return operand_1 - operand_2;
  else if(Operator == '*') return operand_1 * operand_2;
  else return operand_1/operand_2;
}

//// function to get a character_key
void get_input()
{
  for(int i=0;i<ROWS;i+=1)
  {
    digitalWrite(row_pins[i],LOW);
    for(int j=0;j<COLUMNS;j+=1)
    {
      if(digitalRead(col_pins[j])== LOW)
      {
         input.concat(keys[i][j]);
         delay(DEBOUNCE_DELAY);
         if(input[input.length()-1] == '=')
         {
           check_validity();
           return;
         }
         else if(input[input.length()-1] == '_')
         {
           input = "";
           return;
         }
      }
    }
    digitalWrite(row_pins[i],HIGH);
  }
}


//// Function to get operator and operand tokens from input string
void get_tokens()
{

  //// converting from string to char []
  char* str = new char[input.length()+1];
  input.toCharArray(str,input.length()+1);
  lcd.clear();
  
  //// getting the operator tokens
  operator_token = strtok(str,operand_delimiters);
  char* temp = operator_token;
  lcd.setCursor(0,0);
  while(temp != NULL)
  {
    lcd.print(temp);
    temp = strtok(NULL,operand_delimiters);
    delay(1000);
  }
  
  //// getting the operands  
  input.toCharArray(str,input.length()+1);
  operand_token = strtok(str,operator_delimiters);
  temp = operand_token;
  lcd.setCursor(0,1);
  while(temp != NULL)
  {  
    lcd.print(temp);
    temp = strtok(NULL,operator_delimiters);
    delay(1000);
  }

}

//// ininitializing all pins to HIGH
void init_pins()
{
  for(int i = 0;i<ROWS;i+=1)
  {
    pinMode(row_pins[i],OUTPUT);
    digitalWrite(row_pins[i],HIGH);
  }

  for(int j=0;j<COLUMNS;j+=1)
  {
    pinMode(col_pins[j],INPUT);
    digitalWrite(col_pins[j],HIGH);
  }
}


//// Initializing the LCD
void init_LCD()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Let's Calculate");
  delay(1000);
  lcd.clear();
}

void display_question()
{
  lcd.setCursor(0,0);
  lcd.print(input);
  if(input == "")
  {
    lcd.clear();
  }
}

void setup() 
{ 
  init_pins();
  init_LCD();
}


void loop()
{
  get_input();
  display_question();
  while(valid_exp)
  {
    get_tokens(); 
  }
}
