#include "infraredReceiver.h"
#define SWITCH_TIME 200
infraredReceiver mySensor(8);
int pinState = false;

unsigned long myTime, lastTime;


void setup()
{
  Serial.begin(115200);
  pinMode(8,INPUT);
}

void loop()
{
  /*
    pinState = 10*sin((2*3.14*5*millis())/1000);
    if(pinState>0)
    {
      pinState = 1;
     
    }
    else
    {
      pinState = 0;
    }
    */

    //mySensor.forcePin(pinState);
    
    mySensor.update();

    Serial.println(String("Signal Identity: ") + mySensor.getSignalIdentity());


  delay(20); //changed for ir reciever
}

