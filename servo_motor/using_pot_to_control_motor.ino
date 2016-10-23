// Program to control angle to which servo-motor can turn by using potentiometer
// Here, potentiometer is connected to analog pin AO and servo-motor is connected to pin 11
// Potentiometer value is mapped within 0 and 180 which means motor can rotate 180 degrees clockwise and anticlockwise
// To change range of angle of motor turn, change the map parameters
// To change speed of motor turn, change the delay within 'for' loops

#include <Servo.h>

Servo servo_control;  
float servo_position = 0.0;
float servo_angle;

void setup() 
{
  servo_control.attach(11);
}

void loop() 
{
  servo_angle = map(analogRead(A0), 0, 1023, 0.0, 180.0);
  for (servo_position = 0; servo_position <= servo_angle; servo_position += 1.0) 
  {
    servo_control.write(servo_position);
    delay(20);
  }
  for (servo_position = servo_angle; servo_position >= 0; servo_position -= 1.0) 
  {
    servo_control.write(servo_position);
    delay(20);
  }
}



