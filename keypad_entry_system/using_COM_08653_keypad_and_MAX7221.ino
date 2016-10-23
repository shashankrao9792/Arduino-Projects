/*  This project uses a SparkFun COM-08653 numeric keypad, a Lite-ON LTC-4727JR from Digi-Key(which is a quad, common-cathode, 7-segment display),
      a MAX7221 8-digit LED display driver, a 2N2222 NPN transistor, a 1N4001 diode, a 5V DC miniature relay and a few more components in order to create 
      a prototype electronic keypad entry system.
    numberOfDigits variable sets your LED driver IC with the proper number of digits. 
    numRows and numCols variables store the number of rows and columns on your keypad, 4 and 3, respectively.
    debounceTime variable ensures that the key being pressed is accurately detected.
    doorOpenTime variable sets the amount of time the door will be held open.
    The strikePin variable defines which digital pin will be activated when the correct code is entered. This applies power to the relay, 
      which closes to actuate your door lock mechanism.
    slaveSelect variable defines a digital pin that you use to indicate you are sending data. The slave select pin (SS) is a command pin on your IC
      that connects the external pins to the internal circuitry.
    code[] stores the access code digits; codeBuffer[], stores the keys that have been pressed.
    DEBUG variable is used for debugging and testing; prints status messages to serial port
    keypressCount variable stores how many digits have been pressed so far
    keyMap is used to store digits which are on the keypad
    sendCommand() is used to make it easier to send instructions to the chip using the SPI interface.Every time an instruction is sent,
      the SlaveSelect pin is set to LOW, the byte corresponding to the command to be issued to the chip is sent, the byte with the value for the
      command is sent, and then set SlaveSelect back to HIGH.
    clearDisplay() function sets all the digits to be blank
    getKey() function goes through each of the digital pins connected to the column pins of the keypad and sets the pin for LOW. It then
      checks to see if any row pins are now also LOW. The pull-up resistors used in setup() keep the row pins HIGH — unless a key has been pressed,
      connecting it to a LOW column pin
    In the unlock() function, the four sendCommand() instructions print the message "HI" to the display. The strikePin is written HIGH, which
      will provide power to the transistor controlling the relay. When it activates, power is allowed to pass to the unlocking mechanism for the duration
      specified by doorOpenTime . Then sets strikePin to LOW to lock the door again
*/

const int numberOfDigits = 4;
const int numRows = 4;
const int numCols = 3;
const int debounceTime = 20;
const int doorOpenTime = 5000;
const int strikePin = 9;
const int slaveSelect = 10;
char code[4]= {'1','2','3','4'};
char codeBuffer[4];
boolean DEBUG=true;
int keypressCount=0;

const char keyMap[numRows][numCols] = {   { '1', '2', '3' },
                                          { '4', '5', '6' },
                                          { '7', '8', '9' },
                                          { '*', '0', '#' }  };

const int rowPins[numRows] = { 7, 2, 3, 5  };
const int colPins[numCols] = { 6, 8 ,4 };

void setup()
{
  if (DEBUG)
  {
    Serial.begin(9600);
  } 

  SPI.begin();
  pinMode(slaveSelect, OUTPUT);
  sendCommand(12,1); 
  sendCommand(15,0); 
  sendCommand(10,8); 
  sendCommand(11, numberOfDigits);
  sendCommand(9,255);
  pinMode(strikePin,OUTPUT);
  
  for (int row = 0; row < numRows; row++)
  {
    pinMode(rowPins[row],INPUT); 
    digitalWrite(rowPins[row],HIGH);
  }
  for (int column = 0; column < numCols; column++)
  {
    pinMode(colPins[column],OUTPUT);
    digitalWrite(colPins[column],HIGH);
  }
  clearDisplay();                        
}

void loop()
{
  char key = getKey();
  codeBuffer[keypressCount]=key;
  if( key != 0) 
  {
    sendCommand(keypressCount+1, key);

    if (DEBUG)
    {
      Serial.print("Digit ");
      Serial.println(keypressCount);
      Serial.print("Got key: ");
      Serial.println(key);
      Serial.print("Buffer: ");
      Serial.print(codeBuffer[0]);
      Serial.print(codeBuffer[1]);
      Serial.print(codeBuffer[2]);
      Serial.println(codeBuffer[3]);
      Serial.print("Code: ");
      Serial.print(code[0]);
      Serial.print(code[1]);
      Serial.print(code[2]);
      Serial.println(code[3]);
    }

    keypressCount++;
    if (keypressCount==4)
    {
      delay(500);
      if (memcmp(codeBuffer, code,4)==0) 
      {
        if(DEBUG)
        {
          Serial.println("MATCH!");
        }
        unlock();
      } 
      clearDisplay();
      memset(codeBuffer, 0, 4);
      keypressCount=0;
    }
  }
}

char getKey()
{
  char key = 0;
  for(int column = 0; column < numCols; column++)
  {
    digitalWrite(colPins[column],LOW);
    for(int row = 0; row < numRows; row++)
    {
      if(digitalRead(rowPins[row]) == LOW)
      {
        delay(debounceTime);
        while(digitalRead(rowPins[row]) == LOW);
        key = keyMap[row][column];
      }
    }
    digitalWrite(colPins[column],HIGH);
  }
  return key;
}

void sendCommand(int command, unsigned char value)
{
  digitalWrite(slaveSelect,LOW);
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(slaveSelect,HIGH);
}  

void clearDisplay()
{
  sendCommand(1, '_');
  sendCommand(2, '_'); 
  sendCommand(3, '_');
  sendCommand(4, '_'); 
}

void unlock()
{  
  if(DEBUG)
  {
    Serial.println("Unlocking Door.");
  }
  sendCommand(1, 'o');
  sendCommand(2, 'l');
  sendCommand(3, '1');
  sendCommand(4, 'o');
  digitalWrite(strikePin,HIGH);
  delay(doorOpenTime);
  digitalWrite(strikePin,LOW);
}
