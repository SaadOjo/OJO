#include "infraredDistance.h"

infraredDistance mySensor(3);
float distance;

void setup()
{
  Serial.begin(9600);
  mySensor.init();
}

void loop()
{
  distance = mySensor.getDistance();
  Serial.println(String("The distance is:") + distance);
  delay(1000);
  
}

