/* Stage 5: Send Sensor Value to Serial Monitor
     Written by ScottC on 7/7/2012 */

  int sensorVal = 0;  

  void setup() {
 // Setup Serial communication with computer
    Serial.begin(9600);
  }

  void loop() {
 // Read the value from the sensor:
    sensorVal = constrain(map(analogRead(A0), 200, 800, 0, 100));
 
 // Send the value to the Serial Monitor
    Serial.print("Sensor Value=");
    Serial.println(sensorVal);

 // Interval between readings = 1 second
    delay(1000);                
  }

