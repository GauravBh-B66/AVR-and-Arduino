#include <IRremote.h>
#include <Servo.h>

const int sig_r = 7;
const int sig_s = 8;

int pos=90;
int change = 1;

IRrecv remote(sig_r);
decode_results code;

Servo servo;

const long  right = 0xFE827D;
const long  left = 0xFE42BD;
//const long  cont = 0xFFFFFFFF;
 long prev_val;


void setup()
{
  remote.enableIRIn();
  servo.attach(sig_s);
  servo.write(pos);
  Serial.begin (9600);
}

void loop()
{
  if (remote.decode(&code))
  {
    Serial.println(code.value,HEX);
    switch (code.value)
    {
      case(right):
      {
        prev_val = right;
        pos-=change;
        if (pos <=0){pos=0;}
        Serial.println("RIght>>");
        servo.write(pos);
        break;
      }
      case(left):
      {
        prev_val = left;
        pos+=change;
        if (pos >=180){pos=180;}
        Serial.println("left>>");
        servo.write(pos);
        break;
      }
      case(0xFFFFFFFF):
      {
        if (prev_val == right)
        {
          pos-=change;
          if (pos <=0){pos=0;}
          Serial.println("Continuing RIght>>");
          servo.write(pos);
        }
        else if (prev_val == left)
        {
          pos+=change;
          if (pos >=180){pos=180;}
          Serial.println("Continuing left>>");
          servo.write(pos);
        }
        break;
      }
      default:
      {}
    }
    remote.resume();
  }
}
