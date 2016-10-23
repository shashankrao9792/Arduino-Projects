// This program displays message given in message[] array onto a 8X8 LED matrix one character at a time
// index variable holds the current character in the string being displayed
// offset variable holds how many columns it is offset by
// constant integers define each character's position in an array of integer arrays
// rowPin[] and colPin[] defines which pin each row & column is attached to respectively
// data[] array is used to hold a bitmap of the display
// constant integer arrays such as _A[],_B[],etc is an 8 x 7 bitmap where 1 is on and 0 is off
// letters[] holds the bitmap characters in an array (each character's position corresponds to its previously defined index)
// powers[] is an array holding the powers of 2; used as bit masks when calculating what to display
// loadCharacter() loads the current scroll state frame into the data[] display array
// displayCharacter() is used to set the LEDs on or off as per loaded bitmap
// getChar() returns the index of a given character for converting from a string to a lookup in the array of character bitmaps above

char message[] = "HELLO WORLD! ";

int index = 0;
int offset = 0;

const int A = 0; const int B = 1; const int C = 2; const int D = 3; const int E = 4; const int F = 5; const int G = 6; const int H = 7; const int I = 8; const int J = 9;  
const int K = 10; const int L = 11; const int M = 12; const int N = 13; const int O = 14; const int P = 15; const int Q = 16; const int R = 17; const int S = 18; const int T = 19;
const int U = 20; const int V = 21; const int W = 22; const int X = 23; const int Y = 24; const int Z = 25; const int _ = 26; const int EXCLM = 27; const int CHECK = 28;

int rowPin[] = {2,3,4,5,6,7,8,9};
int colPin[] = {17,16,15,14,13,12,11,10};
byte data[] = {0,0,0,0,0,0,0,0};        

const int _A[] = {B0001000,
                  B0010100,
                  B0100010,
                  B1000001,
                  B1111111,
                  B1000001,
                  B1000001,
                  B0000000};

const int _B[] = {B1111110,
                  B0100001,
                  B0100001,
                  B0111110,
                  B0100001,
                  B0100001,
                  B1111110,
                  B0000000};

const int _C[] = {B0011111,
                  B0100000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B0100000,
                  B0011111,
                  B0000000};

const int _D[] = {B1111100,
                  B0100010,
                  B0100001,
                  B0100001,
                  B0100001,
                  B0100010,
                  B1111100,
                  B0000000};

const int _E[] = {B1111111,
                  B1000000,
                  B1000000,
                  B1111100,
                  B1000000,
                  B1000000,
                  B1111111,
                  B0000000};

const int _F[] = {B1111111,
                  B1000000,
                  B1000000,
                  B1111100,
                  B1000000,
                  B1000000,
                  B1000000,
                  B0000000};

const int _G[] = {B0011111,
                  B0100000,
                  B1000000,
                  B1001111,
                  B1000001,
                  B0100001,
                  B0011111,
                  B0000000};

const int _H[] = {B1000001,
                  B1000001,
                  B1000001,
                  B1111111,
                  B1000001,
                  B1000001,
                  B1000001,
                  B0000000};

const int _I[] = {B1111111,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B1111111,
                  B0000000};

const int _J[] = {B0001111,
                  B0000001,
                  B0000001,
                  B0000001,
                  B0000001,
                  B1000001,
                  B0111110,
                  B0000000};

const int _K[] = {B1000011,
                  B1000100,
                  B1001000,
                  B1110000,
                  B1001000,
                  B1000100,
                  B1000011,
                  B0000000};

const int _L[] = {B1000000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B1111111,
                  B0000000};

const int _M[] = {B1110110,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B0000000};

const int _N[] = {B1000001,
                  B1100001,
                  B1010001,
                  B1001001,
                  B1000101,
                  B1000011,
                  B1000001,
                  B0000000};

const int _O[] = {B0011100,
                  B0100010,
                  B1000001,
                  B1000001,
                  B1000001,
                  B0100010,
                  B0011100,
                  B0000000};

const int _P[] = {B0111110,
                  B0100001,
                  B0100001,
                  B0111110,
                  B0100000,
                  B0100000,
                  B0100000,
                  B0000000};

const int _Q[] = {B0011100,
                  B0100010,
                  B1000001,
                  B1000001,
                  B1000101,
                  B0100010,
                  B0011101,
                  B0000000};

const int _R[] = {B1111110,
                  B0100001,
                  B0100001,
                  B0101110,
                  B0100100,
                  B0100010,
                  B0100001,
                  B0000000};

const int _S[] = {B0111111,
                  B1000000,
                  B1000000,
                  B0111110,
                  B0000001,
                  B0000001,
                  B1111110,
                  B0000000};

const int _T[] = {B1111111,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0000000};

const int _U[] = {B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B0111110,
                  B0000000};

const int _V[] = {B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B0100010,
                  B0010100,
                  B0001000,
                  B0000000};
                  
const int _W[] = {B1000001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B0110110,
                  B0000000};

const int _X[] = {B1000001,
                  B0100010,
                  B0010100,
                  B0001000,
                  B0010100,
                  B0100010,
                  B1000001,
                  B0000000};

const int _Y[] = {B1000001,
                  B0100010,
                  B0010100,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0000000};

const int _Z[] = {B1111111,
                  B0000010,
                  B0000100,
                  B0111110,
                  B0010000,
                  B0100000,
                  B1111111,
                  B0000000};
                  
const int __[] = {B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000};

const int _EXCLM[] = {B0000010,
                      B0000010,
                      B0000010,
                      B0000010,
                      B0000010,
                      B0000000,
                      B0000010,
                      B0000000};          

const int _CHECK[] = {B1010101,
                      B0101010,
                      B1010101,
                      B0101010,
                      B1010101,
                      B0101010,
                      B1010101,
                      B0000000};

const int * letters[] = {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,__,_EXCLM,_CHECK};
const int powers[] = {1,2,4,8,16,32,64,128};

void setup()
{ 
  for(int i = 0; i < 8; i++)
  {
    pinMode(rowPin[i], OUTPUT);
    pinMode(colPin[i], OUTPUT);
  }
}
 
void loop()
{
  loadCharacter();
  displayCharacter(data, 40);
}

void loadCharacter()
{
  int currentChar = getChar(message[index]);
  int nextChar = getChar(message[index+1]);
  for(int row=0; row < 8; row++)
  {
    data[row] = 0;
    for(int column=0; column < 8; column++)
    {
      data[row] = data[row] + ((powers[column] & (letters[currentChar][row] << offset)));
      data[row] = data[row] + (powers[column] & (letters[nextChar][row] >> (8-offset) ));
    }
  }
  offset++;
  if(offset==8)
  {
    offset = 0; 
    index++; 
    if(index == sizeof(message)-2)
    {
      index=0;
    }
  }
}

void displayCharacter(byte * data, unsigned long duration)
{
  unsigned long start = millis();
  while (start+duration > millis())
  {
    for(int column = 0; column < 8; column++)
    {
      for(int i = 0; i < 8; i++)
      {
        digitalWrite(rowPin[i], LOW);
      }
      for(int i = 0; i < 8; i++)
      {
        if(i == column)
        {
          digitalWrite(colPin[i], LOW);
        }
        else
        {
          digitalWrite(colPin[i], HIGH); 
        }
      }
      for(int row = 0; row < 8; row++)
      {
        int bit = (data[column] >> row) & 1;
        if(bit == 1)
        {
          digitalWrite(rowPin[row], HIGH);
        }
      }
    } 
  }
}

int getChar(char character)
{
  int returnValue = CHECK;
  switch(character)
  {
    case 'A': returnValue = A; break;
    case 'a': returnValue = A; break;
    case 'B': returnValue = B; break;
    case 'b': returnValue = B; break;
    case 'C': returnValue = C; break;
    case 'c': returnValue = C; break;
    case 'D': returnValue = D; break;
    case 'd': returnValue = D; break;
    case 'E': returnValue = E; break;
    case 'e': returnValue = E; break;
    case 'F': returnValue = F; break;
    case 'f': returnValue = F; break;
    case 'G': returnValue = G; break;
    case 'g': returnValue = G; break;
    case 'H': returnValue = H; break;
    case 'h': returnValue = H; break;
    case 'I': returnValue = I; break;
    case 'i': returnValue = I; break;
    case 'J': returnValue = J; break;
    case 'j': returnValue = J; break;
    case 'K': returnValue = K; break;
    case 'k': returnValue = K; break;
    case 'L': returnValue = L; break;
    case 'l': returnValue = L; break;
    case 'M': returnValue = M; break;
    case 'm': returnValue = M; break;
    case 'N': returnValue = N; break;
    case 'n': returnValue = N; break;
    case 'O': returnValue = O; break;
    case 'o': returnValue = O; break;
    case 'P': returnValue = P; break;
    case 'p': returnValue = P; break;
    case 'Q': returnValue = Q; break;
    case 'q': returnValue = Q; break;
    case 'R': returnValue = R; break;
    case 'r': returnValue = R; break;
    case 'S': returnValue = S; break;
    case 's': returnValue = S; break;
    case 'T': returnValue = T; break;
    case 't': returnValue = T; break;
    case 'U': returnValue = U; break;
    case 'u': returnValue = U; break;
    case 'V': returnValue = V; break;
    case 'v': returnValue = V; break;
    case 'W': returnValue = W; break;
    case 'w': returnValue = W; break;
    case 'X': returnValue = X; break;
    case 'x': returnValue = X; break;
    case 'Y': returnValue = Y; break;
    case 'y': returnValue = Y; break;
    case 'Z': returnValue = Z; break;
    case 'z': returnValue = Z; break;
    case ' ': returnValue = _; break;
    case '!': returnValue = EXCLM; break;
  }
  return returnValue;
}
