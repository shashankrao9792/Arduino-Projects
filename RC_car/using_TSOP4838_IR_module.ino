/*  This is a program for a simple RC car built using a remote control, TSOP4838 Infrared Receiver Module and two continuous-rotation servo motors.
    This program has to be executed in two steps- first the keyCode being sent from the IR remote needs to be identified for the different keys
      which will be used to drive the car.
    For this, the DEBUG_1 variable is set to true, the arduino is run and different keys which will be used for the car are pressed. This 
      will give the keyCode values for the buttons on the IR remote.
    Once the keyCode values are obtained, they are used in the switch condition within loop() in order to control the different aspects 
      of the motor movement.
*/

#include <Servo.h>
#include <IRremote.h>

const int irReceivePin = 2; 
IRrecv irrecv(irReceivePin);
decode_results results;     
const int rightMotorPin = 9;
const int leftMotorPin = 10;
Servo rightServo;
Servo leftServo;
int rightSpeed=90;
int leftSpeed=90;
long keyCode=0;
boolean DEBUG_1 = false; 

void setup()
{
  if(DEBUG_1)
  {
    Serial.begin(9600);
  }
  irrecv.enableIRIn();
  leftServo.attach(9);
  rightServo.attach(10);
  pinMode(rightMotorPin, OUTPUT);
  pinMode(leftMotorPin, OUTPUT);
}

void loop() 
{
  if( irrecv.decode(&results))
  {
    keyCode=results.value;
    if(keyCode != -1)
    {
      switch (keyCode)
      {
        case 50174055:
            Serial.println("Forward");
            leftSpeed-=1;
            rightSpeed+=1; 
            break;
        case 50182215:
            Serial.println("Backward");
            leftSpeed+=1; 
            rightSpeed-=1; 
            break; 
        case 50168955: 
            Serial.println("Stop");
            leftSpeed=90; 
            rightSpeed=90; 
            break; 
        case 50152125:
            Serial.println("Turn Left");
            leftSpeed-=1;
            rightSpeed-=1;  
            break;
        case 50135805:
            Serial.println("Turn Right");
            leftSpeed+=1;
            rightSpeed+=1;
            break;
        case 50139885:
            Serial.println("TURBO!!");
            leftSpeed=leftSpeed-50;
            rightSpeed=rightSpeed+50;
            break;
      }
      if(DEBUG_1)
      {
        Serial.println(keyCode);
        showReceivedData();
        Serial.print(leftSpeed);
        Serial.print(", ");
        Serial.println(rightSpeed);
      }
    }
    irrecv.resume();
  }
  updateMotors();
  delay(10);
}

void showReceivedData()
{
  if (results.decode_type == UNKNOWN)
  {
    Serial.println("-Could not decode message");
  }
  else
  {
    if (results.decode_type == NEC) 
    {
      Serial.print("- decoded NEC: ");
    }
    else if (results.decode_type == SONY) 
    {
      Serial.print("- decoded SONY: ");
    }
    else if (results.decode_type == RC5) 
    {
      Serial.print("- decoded RC5: ");
    }
    else if (results.decode_type == RC6) 
    {
      Serial.print("- decoded RC6: ");
    }
    Serial.print("Value = ");
    Serial.println( results.value, DEC);
  }
}

void updateMotors()
{
  leftServo.write(leftSpeed);
  rightServo.write(rightSpeed);
}
