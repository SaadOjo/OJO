#include "controller.h"
infraredDistance mySensor(1);
controller myController(mySensor);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  myController.followRobot(20);
  delay(100);
}
