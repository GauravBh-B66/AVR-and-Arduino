/*Perform the following actions:

1. Trigger pin to digital pin 3
2. Echo pin to digital pin 4
3. Servo signal pin (yellow) to digial pin 8
*/


#include <Servo.h>
int trig=3;
int echo=4;
int sig=8;
int i;
float t,d,dist;
Servo s;

float distance()
{
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  t=pulseIn(echo, HIGH);
  return(d=t*0.0343/2);
}

void knock()
{
  s.write(30);
  delay(750);
  s.write(0);
}

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(sig, OUTPUT);
  s.attach(sig);
  Serial.begin(9600);
  i=0;
  s.write(0);
}

void loop()
{
  //s.write(0+(90*(i%2)));
  s.write(0);
  dist=distance();
  Serial.print(dist);
  Serial.println("cm.");
  if(dist<=15)
  {
    knock();
    Serial.println("Knocked");
  }
  delay(100);
  //i++
}
