#include <LiquidCrystal.h>
#define V_REF 5000 //// Maximum temp
#define ADC_RES 1024 //// 10 bit ADC
#define LM_Sensitivity 10 //// Sensitivity of LM35
LiquidCrystal lcd(2,3,4,5,6,7);


int fan_pin=10; //// defining fan_pin
int LM_pin = A0; //// defining the temperature sensor pin 
int temperature; //// global variable to store temperature
int voltage_in_bits; //// the 10 bit ADC will give the analog voltage in bits.
int voltage; //// the voltage in volts
int step_size = 4.9; //// V_REF/ADC_RES after rounding off


//// Initializing the LCD
void init_lcd()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Initializing LCD");
  delay(2000);
  lcd.clear();
}

//// Operating the fan based on the temperature value
void operate_fan()
{
  if(temperature >= 30)
  {
    digitalWrite(fan_pin,HIGH);
  }
  else
  {
    digitalWrite(fan_pin,LOW);
  }
}

//// Reading analog input and getting the temperature of the room
void get_temperature()
{
  voltage_in_bits = analogRead(LM_pin);
  voltage = step_size*voltage_in_bits; //// voltage in milli volts
  temperature = voltage/LM_Sensitivity; //// getting temp.
}

//// function to display temperature
void display_temperature()
{
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  delay(1000);
  lcd.clear();
}
void setup() 
{
  init_lcd();
}

void loop() 
{
  get_temperature();
  display_temperature();
  operate_fan();
}
