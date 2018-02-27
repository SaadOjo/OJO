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
  //direction = mySensor.getDirection();
  //Serial.println(String("The direction is:") + direction);
  //Serial.println(direction); 
  
  
  leftVoltage = mySensor.getLeftVoltage();
  rightVoltage = mySensor.getRightVoltage();
  Serial.print("left Voltage:");
  Serial.print(leftVoltage,3);
  Serial.print(", rightVoltage:");
  Serial.println(rightVoltage,3);
  
  delay(100);  
}

