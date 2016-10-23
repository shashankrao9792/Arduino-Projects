// program for a simple 8-key elctronic piano
// digital pins 2-9 are connected to push buttons and piezo buzzer is connected to pin 13

int pin_C = 2;
int pin_D = 3;
int pin_E = 4;
int pin_F = 5;
int pin_G = 6;
int pin_A = 7;
int pin_B = 8;
int pin_Cup = 9;

int pin_speaker = 13;

int note_C = 0;
int note_D = 0;
int note_E = 0;
int note_F = 0;
int note_G = 0;
int note_A = 0;
int note_B = 0;
int note_Cup = 0;

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
int Cur_tone = 0;

void setup()
{
  pinMode(pin_C, INPUT);
  pinMode(pin_D, INPUT);
  pinMode(pin_E, INPUT);
  pinMode(pin_F, INPUT);
  pinMode(pin_G, INPUT);
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  pinMode(pin_Cup, INPUT);
  pinMode(pin_speaker, OUTPUT);
}

void loop()
{
  note_C = digitalRead(pin_C);
  note_D = digitalRead(pin_D);
  note_E = digitalRead(pin_E);
  note_F = digitalRead(pin_F);
  note_G = digitalRead(pin_G);
  note_A = digitalRead(pin_A);
  note_B = digitalRead(pin_B);
  note_Cup = digitalRead(pin_Cup);
  if((note_C == HIGH) || (note_E == HIGH) || 
     (note_G == HIGH) || (note_D == HIGH) || 
     (note_F == HIGH) || (note_A == HIGH) || 
     (note_B == HIGH) || (note_Cup == HIGH))
  { 
    if (note_C == HIGH)
    {
      Cur_tone = tones[0];
    } 
    else if (note_E == HIGH)
    {
      Cur_tone = tones[1];
    }
    else if (note_G == HIGH)
    {
      Cur_tone = tones[2];
    }
    else if (note_D == HIGH)
    {
      Cur_tone = tones[3];
    }
    else if (note_F == HIGH)
    {
      Cur_tone = tones[4];
    }
    else if (note_A == HIGH)
    {
      Cur_tone = tones[5];
    }
    else if (note_B == HIGH)
    {
      Cur_tone = tones[6];
    }
    else if (note_Cup == HIGH)
    {
      Cur_tone = tones[7];
    }
    tone(pin_speaker, Cur_tone, 10);
  }
  else
  {
    noTone(10);
  }
}
