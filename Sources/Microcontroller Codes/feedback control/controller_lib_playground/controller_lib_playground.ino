#include "controller.h"
#include "sensor.h"
robotMotion myMotion(5,6);
sensor mySensor; //pass pins from here
controller myController(mySensor, myMotion);

// TEST DEFINITIONS
#define ROBOT_TEST_FOLLOW_TIME 5000
/*
 Notes: 
 1) The follow last speed is taken from the propotional control. This will fail to work when the robot is accelerating

 2) Can only handle one leave command

 !!!! Uncompilable there is unwritten function !!!
*/
bool robotVisibilityState = true;
unsigned char leaveState = 0;
bool followingState = true;

bool testFirst = true;
bool pulse = false;

void setup()
{
  Serial.begin(115200);
  myController.setMaxSpeed(100);
  myController.setMinSpeed(0);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, remoteISR ,FALLING);//PIN 2
}

void loop()
{

if(pulse)
{
  if(testFirst)
  {
    
    followingState = false;
    myController.forceFirstLoop();
    pulse = false;
    testFirst = false;
    Serial.println("Intterrupt"); 
  }
}

  /*
  
  if(millis() < 3000)
  {
   // myController.forceMotors(50, 0);
  }
  else
  {
   // leaving();
   followingState = false;
  }
  
*/
/*
if(millis() > ROBOT_TEST_FOLLOW_TIME)
{
  if(testFirst)
  {
    followingState = false;
    myController.forceFirstLoop();
    testFirst = false;

    Serial.println("Test event happened!");
  }
  
}
*/

  switch(followingState)
  {
    case false:
      leaving();
      break;

    case true:
      following();
      break;
  }
  

delay(100);

}



void following(void)
{
   switch(robotVisibilityState)
  {
    case false:
      Serial.println("A working!");
      if(!myController.followRobot(15))
      {
        robotVisibilityState = true;
      }
      break;

    case true:
      Serial.println("B working!");
      if(myController.findMarker())
      {
        robotVisibilityState = false; 
      }
      break;
  }
}

void leaving(void)
{
    switch(leaveState)
  {
    case 0:
      if(myController.lateralExit())
      {
        leaveState = 1;
      }
      break;
    case 1:
      if(myController.moveBack())
      {
        leaveState = 2;
      }
      break;
    case 2:
      Serial.println("doing nothing!");
      //Test Code
      //followingState = true; //Un comment this
      break;
  }
}

void remoteISR() 
{
  pulse = true;
}

