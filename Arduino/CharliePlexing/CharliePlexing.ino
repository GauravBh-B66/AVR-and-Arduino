#define pin1 5
#define pin2 6
#define pin3 7

#define t 100


void charlie(int x,int y, int z)
{
  pinMode(x,OUTPUT);
  pinMode(y,OUTPUT);
  pinMode(z,INPUT);
  
  digitalWrite(x,HIGH);
  digitalWrite(y,LOW);
  digitalWrite(z,LOW);
}



void setup()
{
  
}

void loop()
{
  charlie(pin1, pin2, pin3);
  delay(t);
  charlie(pin2, pin1, pin3);
  delay(t);
  
  charlie(pin1, pin3, pin2);
  delay(t);
  charlie(pin3, pin1, pin2);
  delay(t);
  
  charlie(pin2, pin3, pin1);
  delay(t);
  charlie(pin3, pin2, pin1);
  delay(t);
}
