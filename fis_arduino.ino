#include <Servo.h>

Servo Servo1, Servo2, Servo3; // create servo object to control a servo

int i, time, obstacle;
int pos1, pos2, pos3; 
int pos1R, pos2R, pos3R; 
int phase=45;
int velocity=2000; 
int maxDeflexion=40; 
int maxDefobs=30; 
int actualTime;
float shift;
const int center1=98; 
const int center2=90;
const int center3=105;
const int sens_SX=5; 
const int sens_DX=6; 
const int lostTime=3000;

void setup()
{
Servo1.attach(4); 
Servo2.attach(3); 
Servo3.attach(2); 
pinMode(sens_SX, INPUT);
pinMode(sens_DX, INPUT);
pinMode(13, OUTPUT);
time=velocity/360;
shift=0;

}

void loop()
{
for (i=0; i<360; i++) {

pos1 = i+2*phase;
pos2 = i+phase;
pos3 = i;

if (pos1>359) pos1-=360;
if (pos2>359) pos2-=360;
if (pos3>359) pos3-=360;

if (pos1>179) pos1=360-pos1; 
if (pos2>179) pos2=360-pos2;
if (pos3>179) pos3=360-pos3; 

pos1R=map(pos1,0,180,center1-maxDeflexion-obstacle,center1+maxDeflexion-obstacle);
pos2R=map(pos2,0,180,center2-maxDeflexion-obstacle,center2+maxDeflexion-obstacle);
pos3R=map(pos3,0,180,center3-maxDeflexion-obstacle,center3+maxDeflexion-obstacle);

Servo1.write(pos1R); 
Servo2.write(pos2R); 
Servo3.write(pos3R); 
delay(time);

pos1R=map(pos1,0,180,center1-maxDeflexion-obstacle,center1+maxDeflexion-obstacle);
pos2R=map(pos2,0,180,center2-maxDeflexion-obstacle,center2+maxDeflexion-obstacle);
pos3R=map(pos3,0,180,center3-maxDeflexion-obstacle,center3+maxDeflexion-obstacle);

obstacle=int(shift);
  
if (digitalRead(sens_DX)==0) { 
if (obstacle<maxDefobs) shift=shift+0.05; 
actualTime=millis();
}
if (digitalRead(sens_SX)==0) { 
if (obstacle > (-maxDefobs)) shift=shift-0.05;
actualTime=millis();
}

if (digitalRead(sens_SX)==1 && digitalRead(sens_SX)==1 && obstacle!=0)
if (millis()>actualTime+lostTime) {
if (shift>0) shift=shift-0.05;
if (shift<0) shift=shift+0.05;
}
}
}
