/* Simple Serial ECHO script : Written by ScottC 06/07/2012 */
/* Stage 4: Double doubler */

/* Global variables needed for programming workflow
   ------------------------------------------------------
   byteRead: holds the value being read from the COM port
   num1: holds the number before the decimal point
   num2: holds the number after the decimal point
   complNum: holds the complete number (before multiplation)
   answer: holds the final value after multiplication
   counter: is used to convert num2 to the number after the decimal
   numOfDec: counts the numbers after the decimal point
   mySwitch: enables the switch between num1 and num2  */
   
   byte byteRead;
   double num1, num2;
   double complNum,answer,counter;
   int numOfDec;
   boolean mySwitch=false;


   void setup() {                
/* Turn the Serial Protocol ON and 
   initialise num1 and num2 variables.*/
     Serial.begin(9600);
     num1=0;
     num2=0;
     complNum=0;
     counter=1;
     numOfDec=0;
   }

   void loop() {
/*  check if data has been sent from the computer: */
     while (Serial.available()) {
     /* read the most recent byte */
        byteRead = Serial.read();
    
       //listen for numbers between 0-9
       if(byteRead>47 && byteRead<59){
          //number found
      
          /* If mySwitch is true, then populate the num1 variable
          otherwise populate the num2 variable*/
          if(!mySwitch){
            num1=(num1*10)+(byteRead-48);
          }else{
            num2=(num2*10)+(byteRead-48);
         
         /* These counters are important */
            counter=counter*10;
            numOfDec++;
          }
       }
    
    /*Listen for an equal sign (byte code 61) 
      to calculate the answer and send it back to the
      serial monitor screen*/
      if(byteRead==61){
   /* Create the double from num1 and num2 */
      complNum=num1+(num2/(counter));
      
   /* Multiply the double by 2 */   
      answer=complNum*2;
      
   /* Send the result to the Serial Monitor */   
      Serial.print(complNum,numOfDec);
      Serial.print(" x 2 = ");
      Serial.println(answer,numOfDec);
      
   /* Reset the variables for the next round */
      num1=0;
      num2=0;
      complNum=0;
      counter=1;
      mySwitch=false;
      numOfDec=0;
      
  /* Listen for the decimal point (byte code 46). This is
     used as a delimiter to help define num1 from num2 */  
     }else if (byteRead==46){
        mySwitch=true;
     }
   }
 }

