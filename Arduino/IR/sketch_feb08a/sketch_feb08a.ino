void setup()
{
  pinMode(7,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}
void loop()
{
  if (digitalRead(7)==LOW)
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(13,LOW);
  }
}
