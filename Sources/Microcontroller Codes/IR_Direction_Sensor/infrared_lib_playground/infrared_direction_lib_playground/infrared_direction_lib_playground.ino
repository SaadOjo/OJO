#include "infraredDirection.h"

infraredDirection mySensor(2,3);
float direction;
float leftVoltage;
float rightVoltage;
void setup()
{
  Serial.begin(115200);
  mySensor.init();
}

void loop()
{
  mySensor.update();
  direction = mySensor.getDirection();
  Serial.print(String("The direction is:") + direction);
  //Serial.println(direction); 
  
  /*
  leftVoltage = mySensor.getLeftVoltage();
  rightVoltage = mySensor.getRightVoltage();
  Serial.print("left Voltage:");
  Serial.print(leftVoltage,3);
  Serial.print(", rightVoltage:");
  Serial.print(rightVoltage,3);
  */
  
  if(mySensor.isVisible())
  {
    Serial.println(" Visibility: TRUE");
  }
  else
  {
    Serial.println(" Visibility: FALSE");
  }
  
  
  delay(100);  
}

