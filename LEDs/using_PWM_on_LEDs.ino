// This program uses PWM on pins 9,10,11 to produce fading effect on LEDs
// There are four functions out of which any one will be randomly called from the main loop
// Function_1 fades on and off all the three LEDs simultaneously 
// Function_2 fades on the green LED and keeps it on for 10s
// Function_3 fades on the red LED and keeps it on for 10s
// Function_4 fades on and off the three LEDs in a random fashion
// If LEDs are placed within translucent material, then Function_4 will produce a random blend of colors outside

const int LED_Red  = 9;
const int LED_Green = 10;
const int LED_Blue  = 11;

int LED_RedVal      = 0;
int LED_RedNewVal   = 0;
int LED_GreenVal    = 0;
int LED_GreenNewVal = 0;
int LED_BlueVal     = 0;
int LED_BlueNewVal  = 0;

int LED_FadeSpeed   = 50;

void setup()
{
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Blue, OUTPUT);
}

void loop() 
{
  int func_select = random(4);
  switch (func_select)
  {
    case 0: Function_1(); break;
    case 1: Function_2(); break;
    case 2: Function_3(); break;
    case 3: Function_4(); break;
  }
}

void Function_1()
{
  for (int count=0;count<10;count++)
  {
    for(int x=0; x<255; x++)
    {
      analogWrite(LED_Red, x);
      analogWrite(LED_Green, x);
      analogWrite(LED_Blue, x);
      delay(10);
    }
    for(int x=255; x>0; x--)
    {
      analogWrite(LED_Red, x);
      analogWrite(LED_Green, x);
      analogWrite(LED_Blue, x);
      delay(10);
    }
  }
}

void Function_2()
{
  for(int x=LED_GreenVal; x<255; x++)
  {
    analogWrite(LED_Green, x);
    delay(LED_FadeSpeed);
  }
  for(int x=LED_RedVal; x>0; x--)
  {
    analogWrite(LED_Red, x);
    delay(LED_FadeSpeed);
  }
  for(int x=LED_BlueVal; x>0; x--)
  {
    analogWrite(LED_Blue, x);
    delay(LED_FadeSpeed);
  }
  delay(10000);
  for(int x=255;x>0;x--)
  {
    analogWrite(LED_Green, x);
    delay(LED_FadeSpeed);
  }
}

void Function_3()
{
  for(int x=LED_RedVal; x<255; x++)
  {
    analogWrite(LED_Red, x);
    delay(LED_FadeSpeed);
  }
  for(int x=LED_GreenVal; x>0; x--)
  {
    analogWrite(LED_Green, x);
    delay(LED_FadeSpeed);
  }
  for(int x=LED_BlueVal; x>0; x--)
  {
    analogWrite(LED_Blue, x);
    delay(LED_FadeSpeed);
  }
  delay(10000);
  for(int x=255; x>0; x--)
  {
    analogWrite(LED_Red, x);
    delay(LED_FadeSpeed);
  }
}

void Function_4()
{
  LED_RedNewVal= random(255);
  if (LED_RedVal < LED_RedNewVal)
  {
    for (int x=LED_RedVal; x<LED_RedNewVal; x++) 
    {
      analogWrite(LED_Red, x);
      delay(LED_FadeSpeed);
    }
  }
  else 
  {
    for (int x=LED_RedVal; x>LED_RedNewVal; x--) 
    {
      analogWrite(LED_Red, x);
      delay(LED_FadeSpeed);
    }
  }
  LED_RedVal = LED_RedNewVal;

  LED_GreenNewVal= random(255);
  if (LED_GreenVal < LED_GreenNewVal)
  {
    for (int x=LED_GreenVal; x<LED_GreenNewVal; x++) 
    {
      analogWrite(LED_Green, x);
      delay(LED_FadeSpeed);
    }
  }
  else 
  {
    for (int x=LED_GreenVal; x>LED_GreenNewVal; x--) 
    {
      analogWrite(LED_Green, x);
      delay(LED_FadeSpeed);
    }
  }
  LED_GreenVal=LED_GreenNewVal;

  LED_BlueNewVal= random(255);
  if (LED_BlueVal < LED_BlueNewVal)
  {
    for (int x=LED_BlueVal; x<LED_BlueNewVal; x++) 
    {
      analogWrite(LED_Blue, x);
      delay(LED_FadeSpeed);
    }
  }
  else 
  {
    for (int x=LED_BlueVal; x>LED_BlueNewVal; x--) 
    {
      analogWrite(LED_Blue, x);
      delay(LED_FadeSpeed);
    }
  }
  LED_BlueVal=LED_BlueNewVal;
}
