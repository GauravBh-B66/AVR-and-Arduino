#include<Servo.h>

int radar_angle=0,arrow_angle=0; 
int echoR=4,trigR=5,echoL=6,trigL=7;      
int radar_pin=8,arrow_pin=9;
int input_value,input_angle,start_angle;
int d_th=2;
float d,dL,dR,dL_prev=1000,dR_prev=1000,t;
Servo radar,arrow;


float dist(int trig_pin, int echo_pin)
{
  digitalWrite(trig_pin,HIGH);
  delay(10);
  digitalWrite(trig_pin,LOW);
  t=pulseIn(echo_pin, HIGH);
  d=t*0.0343/2;
  return d;
}

void object_detected(float dL, float dR)
{
   digitalWrite(13,HIGH);
   delay(100);
   digitalWrite(13,LOW);
   delay(100);
   digitalWrite(13,HIGH);
   delay(100);
   digitalWrite(13,LOW);
   follow_object(dL,dR);
}

void clockwise(int start_angle )
{
  Serial.println("Clockwise Motion started");
  for (radar_angle=start_angle;radar_angle>=0;radar_angle-=5)                //Anti-Clockwise Motion of Radar
  {
    radar.write(radar_angle);
    if(dL<dL_prev){dL_prev=dL;}
    if(dR<dR_prev){dR_prev=dR;}
    dL=dist(trigL,echoL);
    dR=dist(trigR,echoR);
    delay(100);
    Serial.print(dL);
    Serial.print("  ");
    Serial.println(dR);
    if((dL<30)&&abs(dL-dR)<d_th)
     {
      Serial.println("Object Detected");
      object_detected(dL,dR);
      //follow_object(dL,dR);
     }
    radar_angle=radar.read();
   }
 }

void anti_clockwise(int start_angle)
{
  Serial.println("Anti-Clockwise Motion started");
  for (radar_angle=start_angle;radar_angle<=180;radar_angle+=5)                //Anti-Clockwise Motion of Radar
  {
    radar.write(radar_angle);
    if(dL<dL_prev){dL_prev=dL;}
    if(dR<dR_prev){dR_prev=dR;}
    dL=dist(trigL,echoL);
    dR=dist(trigR,echoR);
    delay(100);
    Serial.print(dL);
    Serial.print("  ");
    Serial.println(dR);
    if((dL<30)&&abs(dL-dR)<d_th)
     {
      Serial.println("Object Detected");
      object_detected(dL,dR);
     }
     radar_angle=radar.read();
   }
}
void follow_object(float dl_prev, float dr_prev)
{
  int dl,dr;
  Serial.println(" Now following Object");
  Serial.println(dl_prev);
  Serial.println(dr_prev);
  research: 
        dl=dist(trigL,echoL);
        Serial.print("LEFT ");
        Serial.print(dl);
        dr=dist(trigR,echoR);
        Serial.print("        RIGHT ");
        Serial.println(dr);
        delay(1000);
        if((dr-dl)>30)                                //(dl_prev-dl)>5)&&
        {
          while(abs(dl-dr)>=2)
          {
            Serial.println("Turning Left");
            radar.write(radar.read()+1);
            dl=dist(trigL,echoL);
            dr=dist(trigR,echoR);
          }
        }
        else if((dl-dr)>30)                           //(dr_prev-dr)>5)&&
        {
          while(abs(dl-dr)>=2)
          {
            Serial.println("Turning Right");
            radar.write(radar.read()-1);
            dl=dist(trigL,echoL);
            dr=dist(trigR,echoR);
          }
        }
        else {goto research;}
      }
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(echoL,INPUT);
  pinMode(echoR,INPUT);
  pinMode(trigL,OUTPUT);
  pinMode(trigR,OUTPUT);
  radar.attach(radar_pin);
  arrow.attach(arrow_pin);
  Serial.begin(9200);
}

void loop()
{
  anti_clockwise(0);
  clockwise(180);
}
