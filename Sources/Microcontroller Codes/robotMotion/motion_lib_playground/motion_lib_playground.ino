#include "robotMotion.h"

robotMotion myMotion(5,6); // (LEFT, RIGHT)

#define IN_BUFFER_SIZE 256
char inputArray[IN_BUFFER_SIZE];
char inChar;
void setup()
{
  Serial.begin(9600);
  myMotion.init();
  
  myMotion.setSpeed(40);
  myMotion.setDirection(0);
  myMotion.run();
  delay(1000);

  myMotion.setSpeed(100);
  myMotion.setDirection(0);
  myMotion.run();
  delay(1000);

  myMotion.setSpeed(40);
  myMotion.setDirection(0);
  myMotion.run();
  delay(1000);

  myMotion.setSpeed(40);
  myMotion.setDirection(-100);
  myMotion.run();
  delay(1000);

  myMotion.setSpeed(40);
  myMotion.setDirection(+100);
  myMotion.run();
  delay(1000);

    myMotion.setSpeed(0);
  myMotion.setDirection(+100);
  myMotion.run();
  
}

void loop()
{
/*
  if(Serial.available()>0)
  {
    inChar = Serial.read();
    
    inChar = inChar - 48;
    inChar = inChar*10;
    int s = inChar; 
    Serial.println(s);
    myMotion.setDirection(s);
  }
*/

  
  
//myMotion.run();
  //Serial.println("calisiyor");
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

