//Inclusion of libraries required
#include <DS3231.h>
#include <Wire.h>


//Linking the segments of 7-segment display to the digital pins of the Arduino
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8

#define disp0 9
#define disp1 10

byte numbers[] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};
byte digit0,digit1;

//Creating the objects and variables required for working with the RTC Module.
DS3231 rtc;                           //DS3231 is a class and rtc is the object of that class.
RTCDateTime tyme;                     //RTCDateTime is a structure and tyme is the variable of that datatype.



void display_digit0(byte digit)
{
    digitalWrite(disp0,HIGH);
    digitalWrite(disp1,LOW);
    for (int i = 0; i<7;i++)
    {
      int d1 = bitRead(digit,i);
      digitalWrite(i+2,d1);
    }
    for (int k=0;k<7;k++)
    {
      digitalWrite(k+2,HIGH);
    }
}

void display_digit1(byte digit)
{
     digitalWrite(disp0,LOW);
     digitalWrite(disp1,HIGH);
    for (int i = 0; i<7;i++)
    {
      int d1 = bitRead(digit,i);
      digitalWrite(i+2,d1);
    }
    for (int k=0;k<7;k++)
    {
      digitalWrite(k+2,HIGH);
    }
}

void setup()
{
  Serial.begin(9600);
  rtc.begin();
  rtc.setDateTime(__DATE__, __TIME__);
  
  pinMode(disp0,OUTPUT);
  pinMode(disp1,OUTPUT);
  
  for(int seg = A; seg<=G; seg++)
  {
    pinMode(seg, OUTPUT);
    digitalWrite(seg, HIGH);
  }
}

void loop()
{
  
  while(1)              //Ten's place digit of minute
  {
    
 /* tyme = rtc.getDateTime();
    digit1 = numbers[(tyme.minute)/10];
    Serial.print("Digit 1 =");
    Serial.println((tyme.minute)/10);
    display_digit(digit1);

    for(int d0=(tyme.minute)%10; d0<10; d0++)         //One's place digit of minute
    {    
      tyme = rtc.getDateTime();
      digit0 = numbers[(tyme.minute)%10];
      Serial.print("Digit 0 =");
      Serial.println((tyme.minute)%10);
      //display_digit(digit0);
    }*/
    tyme = rtc.getDateTime();
    display_digit0(numbers[(tyme.minute)%10]);
    display_digit1(numbers[(tyme.minute)/10]);
    
    
  }
  
}
