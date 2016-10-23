/*  This program is used to build an RFID tag reader using ID Innovations 20 RFID Module, a miniature Dual In-Line (DIL) reed relay
      and a 125kHz RFID tag.
    relayPin, ledPin variables indicate the pin the relay is connected to and the pin indicator LED is connected to.
    RFIDResetPin variable gives the pin which tells the reader to read again.
    relayOntime variable sets how long the relay is to be operated, once a tag is detected.
    tag1, tag2, tag3, etc. arrays store the RFID tag IDs which are allowed
    checkTag() function checks whatever is inputted into the tagString[] array (whether or not it's a valid tag), against the list of valid tags.
    compareTag() functions takes the two tags- one read through serial and other stored in the program(such as tag1[] or tag2[], etc) and returns 
      boolean value depending on whether the tags are a match or not
    lightLED() and triggerRelay() functions light up the LEDs indicating a known tag has been found
    clearTag() function clears the tagString[] array so that the next reading can be taken
    resetReader() function tells RFID module to get ready for another reading by toggling the reset pin LOW and then HIGH.
*/


const int relayPin = 11;
const int ledPin = 12;  
const int RFIDResetPin = 13;
const int relayOntime = 5000;
char tag1[13] = "4B00DDBF9FB6";
char tag2[13] = "010203AABBCC";
char tag3[13] = "010203AABBDD";

void setup()
{
  Serial.begin(9600);           
  pinMode(RFIDResetPin, OUTPUT);
  pinMode(ledPin, OUTPUT);      
  pinMode(relayPin, OUTPUT);    
  digitalWrite(RFIDResetPin, HIGH);
  Serial.println("Ready.");        
}

void loop()
{
  Serial.println("Looking for a tag...");
  char tagString[13];     
  int index = 0;          
  boolean reading = false;
  while(Serial.available())
  {
    int readByte = Serial.read();    
    if(readByte == 2) 
      reading = true;
    if(readByte == 3) 
      reading = false;
    if((reading && readByte != 2) && (readByte != 10) && (readByte != 13))
    {     
      tagString[index] = readByte;
      index ++;
    }
  }
  checkTag(tagString);
  clearTag(tagString);
  resetReader();
}

void checkTag(char tag[])
{
  if(strlen(tag) == 0) return;
  if(compareTag(tag, tag1))
  {
    lightLED(); 
    triggerRelay();
  }
  else if(compareTag(tag, tag2))
  {
    lightLED();
  }
  else if(compareTag(tag, tag3))
  {
    lightLED();
  }
  else 
  {
    Serial.println("New tag found: "); 
    Serial.println(tag);
    delay(5000);
  }
}

boolean compareTag(char one[], char two[])
{
  if(strlen(one) == 0) return false;
  for(int i = 0; i < 12; i++)
  {
    if(one[i] != two[i]) return false;
  }
  Serial.println("Valid tag found!");
  return true;
}

void lightLED()
{
  digitalWrite(ledPin, HIGH);
  delay(250);                
  digitalWrite(ledPin, LOW); 
}

void triggerRelay()
{
  digitalWrite(relayPin, HIGH); 
  delay(relayOntime);           
  digitalWrite(relayPin, LOW);  
}

void clearTag(char one[])
{
  for(int i = 0; i < strlen(one); i++)
  {
    one[i] = 0; 
  }
} 
  
void resetReader()
{
  digitalWrite(RFIDResetPin, LOW);
  digitalWrite(RFIDResetPin, HIGH);
  delay(150);
}
