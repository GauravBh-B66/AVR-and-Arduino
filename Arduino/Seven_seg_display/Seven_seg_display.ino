#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DP 9

int i;
int t = 1000;
int segment[] = {A,B,C,D,E,F,G};
byte number[] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};


void setup()
{
  for (i=0;i<8;i++)
  {
    pinMode(segment[i],OUTPUT);
    digitalWrite(segment[i],HIGH);
  }
}

void loop()
{
   for (i=0;i<10;i++)
  {
    for (int j=0;j<7;j++)
    {
      int bitt = bitRead(number[i],j);
      digitalWrite(segment[j], bitt); 
    }
    delay(t);
    reset();
  }
 }

void reset()
{
  for (int k=0;k<7;k++)
    {
      digitalWrite(segment[k],HIGH);
    }
}
