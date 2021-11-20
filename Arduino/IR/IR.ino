void setup()
{
  pinMode(A0,INPUT);
  pinMode(7,OUTPUT);
}
void loop()
{
  //int detect=digitalRead(8);
  if (analogRead(A0)<500)
  {
    digitalWrite(7,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(7,HIGH);
    delay(1000);
  }
}
