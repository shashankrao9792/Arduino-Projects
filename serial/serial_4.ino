/* Stage 4: Simple Transmission of a Double
   Written by ScottC on 7/7/2012 */

/* Declare the doubles that will be sent to the Serial Monitor */
   double myDub1, myDub2;

/* This part of the program only runs ONCE */

   void setup(){

   /* Turn ON Serial Communication */
      Serial.begin(9600);
   
   /* Assign a value 1.2345 and 1.9996 to the Doubles being sent */
      myDub1=1.2345;
      myDub2=1.9996;
   
   /*Send the values to the Serial Monitor */
      Serial.print("myDub1 (1.2345) : ");
      Serial.println(myDub1,4);
      Serial.print("myDub2 (1.9996) : ");
      Serial.println(myDub2,3);
   }


   void loop(){
  //Loop does nothing
   }
