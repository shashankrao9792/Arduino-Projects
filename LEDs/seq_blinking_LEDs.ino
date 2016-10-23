// Sequentially lights up a series of LEDs which have been connected to digital pins 4-13
// LEDs blink in order from 4-13 and 13-4
// Use POT to change speed of LED blinks

int current_OnLED = 4;
int LED_dir = 1;
long LED_On_TimePassed = 0;
byte ledPin[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

void setup()
{
  for (int i=0; i<10; i++) 
  {
    pinMode(ledPin[i], OUTPUT);
  }
  LED_On_TimePassed = millis();
}

void loop() 
{
  int LED_OnTime = constrain(map(analogRead(A0), 0, 1023, 10, 100), 10, 100);
  if ((millis() - LED_On_TimePassed) > LED_OnTime) 
  {
    for (int i=0; i<10; i++) 
    {
      digitalWrite(ledPin[i], LOW);
    }
    digitalWrite(ledPin[current_OnLED], HIGH);
    current_OnLED = current_OnLED + LED_dir;
    if (current_OnLED == 9) 
    {
      LED_dir = -1;
    }
    if (current_OnLED == 0) 
    {
      LED_dir = 1;
    }
    LED_On_TimePassed = millis();
  }
}
