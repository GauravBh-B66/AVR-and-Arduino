#include <Servo.h>
int sec=10,steps=1;
Servo s;
int i;

void setup()
{

  s.attach(8);
}

void loop()
{
  
  for(i=0;i<=180;i+=steps)
  {
    s.write(i);
    delay(sec);
  }
  for(i=180;i>=0;i-=steps)
  {
    s.write(i);
    delay(sec);
  }
 // s.write(0);
}
