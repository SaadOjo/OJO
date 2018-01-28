#include "controller.h"
#include "sensor.h"
robotMotion myMotion(5,6);
sensor mySensor; //pass pins from here
controller myController(mySensor, myMotion);

void setup()
{
  Serial.begin(9600);
  myController.setMaxSpeed(30);
}

void loop()
{
  myController.followRobot(15);
  delay(100);
}
