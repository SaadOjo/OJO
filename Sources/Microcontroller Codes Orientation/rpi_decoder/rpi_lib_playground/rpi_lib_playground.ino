#include "rpiDecoder.h"

rpiDecoder myDecoder;

int direction;
int distance;
int orientation;
bool leavingFlagStatus;

unsigned long int startTime;
unsigned long int endTime;

void setup()
{
  Serial.begin(115200);
  pinMode(2,OUTPUT);
}

void loop()
{
  startTime = micros();
  if(myDecoder.update())
  {
    endTime = micros();
    Serial.println(String("Update Time (micros): ") + (endTime - startTime));
    distance = myDecoder.getDistance();
    direction = myDecoder.getDirection();
    orientation = myDecoder.getOrientation();
    leavingFlagStatus = myDecoder.getLeavingFlagStatus();
  
    Serial.println(String("Distance: ") + distance + " ,Direction: " + direction + " ,Orientation: " + orientation + " ,leavingFlagStatus: " + leavingFlagStatus);
    digitalWrite(2,leavingFlagStatus);

    delay(100);
  }
 
}

