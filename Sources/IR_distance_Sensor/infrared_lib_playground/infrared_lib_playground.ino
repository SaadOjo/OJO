#include "infraredDistance.h"

infraredDistance mySensor(2);
float distance;

void setup()
{
  Serial.begin(9600);
  mySensor.init();
}

void loop()
{
  distance = mySensor.getDistance();
  //Serial.println(String("The distance is:") + distance);
  Serial.println(distance);
  delay(100);
  
}

