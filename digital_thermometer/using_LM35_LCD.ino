// Program to display Temperatue using LM35 Temperature sensor onto 16x2 LCD display
// Custom character degreeSymbol created inorder to display degree on LCD
// LM35 to be connected to pin A0; analog value is read and converted to temperature
// Program will cycle between celsius, kelvin & fahrenheit scales of temperature; each scale will be displayed 3s

#include<LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);
const int TempSensor = A0; 
int scale = 1;
float celsius;
float kelvin;
float fahrenheit;
byte degreeSymbol[8] = { 0b00111,
                         0b00101,
                         0b00111,
                         0b00000,
                         0b00000,
                         0b00000,
                         0b00000,
                         0b00000 };

void setup()
{
  pinMode(TempSensor, INPUT);
  lcd.begin(16,2);
  lcd.createChar(1, degreeSymbol);
  lcd.setCursor(0,0);
  lcd.print("    Digital    ");
  lcd.setCursor(0,1);
  lcd.print("  Thermometer   ");
  delay(4000);
  lcd.clear();
}

void loop()
{  
  float TempReading = analogRead(TempSensor);
  celsius = TempReading/2;
  if(scale == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Temperature in C");
    lcd.setCursor(4,1);
    lcd.print(celsius);
    lcd.write(1);
    lcd.print("C");
    scale = 2;
    delay(3000);
    lcd.clear();
  }
  else if(scale == 2)
  {
    kelvin = celsius + 273;
    lcd.setCursor(0,0);
    lcd.print("Temperature in K");
    lcd.setCursor(4,1);
    lcd.print(kelvin);
    lcd.print("K");
    scale = 3;
    delay(3000);
    lcd.clear();
  }
  else if(scale == 3)
  {
    fahrenheit = (celsius*18) + 320;
    fahrenheit = fahrenheit/10;
    lcd.setCursor(0,0);
    lcd.print("Temperature in F");
    lcd.setCursor(4,1);
    lcd.print(fahrenheit);
    lcd.write(1);
    lcd.print("F");
    scale = 1;
    delay(3000);
    lcd.clear();
  }  
}
