#include "rpiDecoder.h"

rpiDecoder myDecoder;

int direction;
int distance;
int orientation;
bool leavingFlagStatus;

void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
}

void loop()
{
  
  if(myDecoder.update())
  {
    distance = myDecoder.getDistance();
    direction = myDecoder.getDirection();
    orientation = myDecoder.getOrientation();
    leavingFlagStatus = myDecoder.getLeavingFlagStatus();
  
    Serial.println(String("Distance: ") + distance + " ,Direction: " + direction + " ,Orientation: " + orientation + " ,leavingFlagStatus: " + leavingFlagStatus);
    digitalWrite(2,leavingFlagStatus);
  }
 
}

