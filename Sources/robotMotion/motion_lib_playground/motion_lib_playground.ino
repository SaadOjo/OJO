#include "robotMotion.h"

robotMotion myMotion(5,6,10,9);

#define IN_BUFFER_SIZE 256
char inputArray[IN_BUFFER_SIZE];
char inChar;
void setup()
{
  Serial.begin(9600);
  myMotion.init();
  myMotion.setSpeed(60);
  myMotion.setDirection(0);
}

void loop()
{

  if(Serial.available()>0)
  {
    inChar = Serial.read();
    
    inChar = inChar - 48;
    inChar = inChar*10;
    int s = inChar; 
    Serial.println(s);
    myMotion.setDirection(-s);
  }


  
  
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

