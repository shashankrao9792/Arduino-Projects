/* Simple Serial ECHO script : Written by ScottC 05/07/2012 */
/* Stage 3: Arduino Maths: Simple Addition */

/* Global variables needed for programming workflow
   byteRead: holds the value being read from the COM port
   num1: holds the entire first number
   num2: holds the entire second number
   answer: holds the sum of num1 and num2
   mySwitch: enables the switch between num1 and num2  */
   
byte byteRead;
long num1, num2,answer;
boolean mySwitch=false;

void setup() {                
/* Turn the Serial Protocol ON and 
   initialise num1 and num2 variables.*/
  Serial.begin(9600);
  num1=0;
  num2=0;
}

void loop() {
   /*  check if data has been sent from the computer: */
  while (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();
    
    //listen for numbers between 0-9
    if(byteRead>='0' && byteRead<='9'){
       //number found
      
       /* If mySwitch is true, then populate the num1 variable
          otherwise populate the num2 variable*/
       if(!mySwitch){
         num1=(num1*10)+(byteRead-'0');
       }else{
         num2=(num2*10)+(byteRead-'0');
       }
    }
    
    /*Listen for an equal sign (byte code 61) 
      to calculate the answer and send it back to the
      serial monitor screen*/
    if(byteRead=='='){
      answer=num1+num2;
      Serial.print(num1);
      Serial.print("+");
      Serial.print(num2);
      Serial.print("=");
      Serial.println(answer);
      
      /* Reset the variables for the next round */
      num1=0;
      num2=0;
      mySwitch=false;
      
    /* Listen for the addition sign (byte code 43). This is
       used as a delimiter to help define num1 from num2 */  
    }else if (byteRead=='+'){
      mySwitch=true;
    }
  }
}
