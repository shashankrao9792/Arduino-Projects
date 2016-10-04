
// I use analogRead to obtain the measure the voltage and express the battery condition visually with LEDs
// The maximum voltage that can be read is 5 V, so we divide 5 by 1,024 (the number of possible values), which equals 
// 0.0048. Therefore, if analogRead() returns 256, then we multiply that reading by 0.0048, which equals 1.2288 V
// AA batteries begin at 1.6V when new and decrease with age
// The output pins(2,4,6) are connected to three different LEDs, one of which will light up depending on battery health

#define batt_new 2 
#define batt_ok  4 
#define batt_old 6 

void setup()
{
	pinMode(batt_new, OUTPUT);
	pinMode(okLED, OUTPUT);
	pinMode(oldLED, OUTPUT);
}
void loop()
{
	int read_value = 0;
	float batt_volts = 0; 
	read_value = analogRead(0); 
	batt_volts = 0.0048 * read_value; 
	if ( batt_volts >= 1.6 ) 
	{
		digitalWrite(batt_new, HIGH);
	} 
	else if ((batt_volts < 1.6) && (batt_volts > 1.4)) 
	{
		digitalWrite(batt_ok, HIGH);
	} 
	else if ( batt_volts <= 1.4 ) 
	{
		digitalWrite(batt_old, HIGH);
	}
}
