#include <IRremote.h>

const int redL = 11;
const int whiteL = 10;
const int blueL = 9;
const int greenL = 8;
const int sig = 7;
const int t = 500;

const long up = 0xFE04FB;
const long right = 0xFE827D;
const long down = 0xFE58A7;
const long left = 0xFE42BD;

IRrecv receiver(sig);         //This is a IRrecv object. The IRrecv object requires signal pin from ir receiver as its parameter.
decode_results arrow;         

void setup()
{
  pinMode (redL, OUTPUT);
  pinMode (whiteL, OUTPUT);
  pinMode (blueL, OUTPUT);
  pinMode (greenL, OUTPUT);
  receiver.enableIRIn();      //Enabling the receiver.
  Serial.begin(9600);
  Serial.println(up);
  //Serial.println(up,HEX);
}

void loop()
{
  
  if (receiver.decode(&arrow))          //The decode function of IRrecv class produces true when there is signal detected in the receiver. This goes low if there is no any signal received. The result is stored in arrow if there is signal present.
  {
    Serial.println(arrow.value);
  switch (arrow.value)
  {
    case up:
    Serial.println("Up button Pressed - White LED is on.");
    digitalWrite(whiteL,HIGH);
    digitalWrite(redL,LOW);
    digitalWrite(blueL,LOW);
    digitalWrite(greenL,LOW);
    delay(t);
    digitalWrite(whiteL,LOW);
    break;

    case right:
    Serial.println("Right button Pressed - BLue LED is on.");
    digitalWrite(whiteL,LOW);
    digitalWrite(redL,LOW);
    digitalWrite(blueL,HIGH);
    digitalWrite(greenL,LOW);
    delay(t);
    digitalWrite(blueL,LOW);
    break;

    case down:
    Serial.println("Down button Pressed - Green LED is on.");
    digitalWrite(whiteL,LOW);
    digitalWrite(redL,LOW);
    digitalWrite(blueL,LOW);
    digitalWrite(greenL,HIGH);
    delay(t);
    digitalWrite(greenL,LOW);
    break;

    case left:
    Serial.println("Left button Pressed - RED LED is on.");
    digitalWrite(whiteL,LOW);
    digitalWrite(redL,HIGH);
    digitalWrite(blueL,LOW);
    digitalWrite(greenL,LOW);
    delay(t);
    digitalWrite(redL,LOW);
    break;

    default:
    digitalWrite(whiteL,LOW);
    digitalWrite(redL,LOW);
    digitalWrite(blueL,LOW);
    digitalWrite(greenL,LOW);
  }
  receiver.resume();
  }
}
