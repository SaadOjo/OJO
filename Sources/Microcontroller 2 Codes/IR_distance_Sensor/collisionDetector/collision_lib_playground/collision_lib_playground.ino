#include "collisionDetector.h"

collisionDetector mySensor(4,5,6,7,8,9,10);
unsigned char danger;

void setup()
{
  Serial.begin(115200);
  mySensor.init();
}

void loop()
{
  danger = mySensor.getAvoidAction();
  Serial.println(danger);
  delay(100);
  
}

