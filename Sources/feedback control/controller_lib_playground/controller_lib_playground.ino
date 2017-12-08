#include "controller.h"
//include library here. declare ibrary inside servo lib as well
robotMotion myMotion(5,6,10,9);
infraredDistance mySensor(1);
controller myController(mySensor, myMotion);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  myController.followRobot(30);
  delay(100);
}
