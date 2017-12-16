#include "robotMotion.h"

robotMotion myMotion(5,6,10,9);

void setup()
{
  Serial.begin(9600);
  myMotion.init();
  myMotion.setSpeed(0);
  myMotion.setDirection(0);
}

void loop()
{
  
myMotion.run();
  //Serial.println("calisyor");
  //delay(1000);
  /*
  for(int i = 0;i<256;i++)
  {
    myMotion.setLeftSpeed(i);
    delay(100);
    Serial.println(i);
  }
    for(int i = 255; i>0; i--)
  {
    myMotion.setLeftSpeed(i);
    delay(100);
    Serial.println(i);
  }
 */
 
}

