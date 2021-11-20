#include <IRremote.h>
const int recv = 7;
IRrecv receiverObj(recv);
decode_results finalResult;

void setup()
{
  receiverObj.enableIRIn();
  Serial.begin(9600);
}

void loop()
{
  if (receiverObj.decode(&finalResult))  
  {
    Serial.println(finalResult.value, HEX);
    Serial.println(finalResult.decode_type);
    switch(finalResult.decode_type)
    {
      case NEC:
      Serial.println("NEC");
      break;
    }
    receiverObj.resume();
  }
}
