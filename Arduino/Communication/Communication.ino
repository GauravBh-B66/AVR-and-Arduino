int MSB=10;
int LSB =8;
int x;
void setup()
{
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  //pinMode(11,OUTPUT);
}

void loop()
{
  digitalWrite(MSB,LOW);
  digitalWrite(9,LOW);
  digitalWrite(LSB,LOW);
  //x=Serial.read();
  //Serial.println(" Enter Numbers betn 0 and 9");
  while (Serial.available()<1);
  {
    //Serial.println(" Enter Numbers betn 0 and 9");
    x=Serial.read();
    delay(2000);
    Serial.println(Serial.available());
  }
  
  switch(x-48)
  {
    case 0:
    {
      Serial.println(x-48);
      digitalWrite(MSB,LOW);
      digitalWrite(9,LOW);
      digitalWrite(LSB,LOW);
      delay(2000);
    }
    break;

    case 1:
    {
      Serial.println(x-48);
      digitalWrite(MSB,LOW);
      digitalWrite(9,LOW);
      digitalWrite(LSB,HIGH);
      delay(2000);
     }
     break;

    case 2:
    {
      Serial.println(x-48);
      digitalWrite(MSB,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(LSB,LOW);
      delay(2000);
    }
    break;

    case 3:
    {
      Serial.println(x-48);
      digitalWrite(MSB,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(LSB,HIGH);
      delay(2000);
    }
    break;

    case 4:
    {
      Serial.println(x-48);
      digitalWrite(MSB,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(LSB,LOW);
      delay(2000);
    }
    break;

    case 5:
    {
      Serial.println(x-48);
      digitalWrite(MSB,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(LSB,HIGH);
      delay(2000);
    }
    break;

    case 6:
    {
      Serial.println(x-48);
      digitalWrite(MSB,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(LSB,LOW);
      delay(2000);
    }
    break;

    case 7:
    {
      Serial.println(x-48);
      digitalWrite(MSB,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(LSB,HIGH);
      delay(2000);
    }
    break;
  }
}
