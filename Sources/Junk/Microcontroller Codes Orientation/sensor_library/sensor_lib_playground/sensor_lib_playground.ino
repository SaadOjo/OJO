#include "infraredDistance.h"
#include "sensor.h"

sensor mySensor(1);
float distance;
float direction;

void setup()
{
  Serial.begin(115200);
  mySensor.init();
  pinMode(2,OUTPUT);
}

void loop()
{
  mySensor.update();
  distance = mySensor.getDistance();
  direction = mySensor.getDirection();

  Serial.println(String("dist: ") + distance + " ,direction: " + direction );
  /*
  if(mySensor.getLeavingFlagStatus())
  {
  Serial.println(mySensor.getLeavingFlagStatus());
  }

  //Serial.println(String("The distance is:") + distance);
  /*
  Serial.print(String("Distance:") + distance);
  Serial.print(String(" ,Direction:") + direction);
  Serial.print(" ");
  switch(mySensor.isVisible())
  {
    case 0: 
      Serial.print("No Sensors Visible");
      break;
    case 1: 
      Serial.print("All Sensors Visible");
      break;
    case 2: 
      Serial.print("Only Primary Sensor Visible");
      break;
    case 3: 
      Serial.print("Only Secondary Sensor Visible");
      break;
    
  }
  Serial.println("");
  Serial.print("Flag status: ");
    switch(mySensor.getLastOneFlagStatus())
  {
    case 0: 
      Serial.print("No flag");
      break;
    case 1: 
      Serial.print("All left");
      break;
    case 2: 
      Serial.print("Only right");
      break;   
  }
  Serial.println(""); */

  digitalWrite(2,mySensor.getLeavingFlagStatus());
  
  delay(100);
}

