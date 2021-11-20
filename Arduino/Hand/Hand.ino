#include <Servo.h>
Servo shoulder, elbow, wrist, finger; 
uint8_t data;
int ud = 90;
int lr = 90;
int ud2 = 90;
int fing = 0;
int step = 1;
void setup() 
{
  shoulder.attach(3);
  elbow.attach(4);
  wrist.attach(5);
  finger.attach(6);
  Serial.begin(9600);
  Serial.println("Press any key to start the robotic hand:");
}

uint8_t tr(void)
{
  do 
  {
    data = Serial.read();
    //Serial.println(data);
    return data;
  }while (Serial.available() == 0);
}

void loop()
{ 
  char key;
  key = tr();
  switch (key)
  {
    case ('w'):
    {
      Serial.println("w");
      elbow.write(ud);
      ud+=step;
      break;
    }
    case ('s'):
    {
      Serial.println("s");
      elbow.write(ud);
      ud-=step;
      break;
    }
    case ('a'):
    {
      Serial.println("a");
      shoulder.write(lr);
      lr+=step;
      break;
    }
    case ('d'):
    {
      Serial.println("d");
      shoulder.write(lr);
      lr-=step;
      break;
    }
    case ('S'):
    {
      Serial.println("S");
      wrist.write(ud2);
      ud2+=step;
      break;
    }
    case ('W'):
    {
      Serial.println("W");
      wrist.write(ud2);
      ud2-=step;
      break;
    }
    
  }
  
}
