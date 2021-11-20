#include <Servo.h>                                      //included the Servo header file.
int i,echo=6,trig=7,ind=13,servoPin=8;                  //connect Echo pin to digital pin 6. Cnnect pin 9 to yellow wire of servo motor.  Yellow is trigger pin and blue is echo pin.    
float t,d;                                              //variables to calculate time and distance                                              
Servo saroj;                       //created a servo object.
float dist()                    //created a function for meassuring distance.
{
    digitalWrite(trig,HIGH);
    delay(10);
    digitalWrite(trig, LOW);
    t=pulseIn(echo,HIGH);
    d=t*0.0343/2;                                      
    return d;
}
void alarm()              //created a function for alarming.
{
      digitalWrite(ind, HIGH);
      delay(300);
      digitalWrite(ind,LOW);
      delay(300);
      d=dist();
}
void setup()              //this portion of code is executed first of all.
{
  pinMode(9,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(ind,OUTPUT);
  saroj.attach(servoPin);
  Serial.begin(9600);      //beginning of the serial monitor.
}
void loop()
{
   for (i=0;i<180;i++)
   {
    saroj.write(i);       //gives the angle of servo motor.
    d=dist();            //calling the function.
    Serial.print(d);
    Serial.println("cm.");
    while(d<2++30)
    {
      alarm();         //calling the function.
      Serial.print(d);
    Serial.println("cm.");
    }
   }
   for (i=170;i>=0;i--)
   {
    saroj.write(i);
    d=dist();
    while(d<20)
    {
      alarm();   
      Serial.print(d);
    Serial.println("cm.");
    }
   }
}
