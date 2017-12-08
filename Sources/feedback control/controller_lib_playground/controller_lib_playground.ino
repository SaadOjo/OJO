#include "controller.h"
#include "sensor.h"
robotMotion myMotion(5,6,10,9);
sensor mySensor; //pass pins from here
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
