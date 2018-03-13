#include "controller.h"
#include "sensor.h"
robotMotion myMotion(5,6);
sensor mySensor; //pass pins from here
controller myController(mySensor, myMotion);

bool robotVisibilityState = true;

void setup()
{
  Serial.begin(115200);
  myController.setMaxSpeed(80);
  myController.setMinSpeed(30);
}

void loop()
{
  if(robotVisibilityState)
  {
    Serial.println("A working!");
    if(!myController.followRobot(15))
    {
      robotVisibilityState = false;
    }
  }
  else
  {
    Serial.println("B working!");
    if(myController.findMarker())
    {
      robotVisibilityState = true; 
    }
  }
 
    
  delay(100);
}
