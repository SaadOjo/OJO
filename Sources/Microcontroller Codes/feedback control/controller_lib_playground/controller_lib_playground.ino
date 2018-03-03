#include "controller.h"
#include "sensor.h"
robotMotion myMotion(5,6);
sensor mySensor; //pass pins from here
controller myController(mySensor, myMotion);

void setup()
{
  Serial.begin(115200);
  myController.setMaxSpeed(30);
  myController.setMinSpeed(30);
}

void loop()
{
  myController.followRobot(15);
  delay(100);
}
