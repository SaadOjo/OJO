#include "controller.h"
#include "sensor.h"
robotMotion myMotion(5,6);
sensor mySensor(1); //Argument is debug info
controller myController(mySensor, myMotion);

// TEST DEFINITIONS
#define ROBOT_TEST_FOLLOW_TIME 5000
/*
 Notes: 
 1) The follow last speed is taken from the propotional control. This will fail to work when the robot is accelerating

 2) Can only handle one leave command (changed not tested)

 3) Lateral Exit uses test conditions for last direction

 !!!! Uncompilable there is unwritten function !!!
*/
bool robotVisibilityState = true;
unsigned char leaveState = 0;
bool followingState = true;

bool ignoreLeaveLineCommand = false;
bool pulse = false;

unsigned long int oldTime;
unsigned long int  myTime;

void setup()
{
  Serial.begin(115200);
  myController.setMaxSpeed(100);
  myController.setMinSpeed(30);
  pinMode(2, OUTPUT);

}

void loop()
{
  mySensor.update();
  Serial.println(mySensor.getLeavingFlagStatus());
  digitalWrite(2,mySensor.getLeavingFlagStatus());
  //updating sensor can have unexpected consequences

if(pulse) //change to take from serial
{
  if(!ignoreLeaveLineCommand)
  {
    
    followingState = false;
    myController.forceFirstLoop();
    pulse = false;
    ignoreLeaveLineCommand = true;
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

  myTime = millis();
  Serial.println(String("Loop Tme: ") + (myTime - oldTime));
  oldTime = myTime;
delay(100);

}



void following(void)
{
   switch(robotVisibilityState)
  {
    case true:
      Serial.println("A working!");
      if(!myController.followRobot(15))
      {
        robotVisibilityState = false;
      }
      break;

    case false:
      Serial.println("B working!");
      if(myController.findMarker())
      {
        robotVisibilityState = true; 
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
      if(myController.rejoin())
      {
        leaveState = 3;
      }
      break;
    case 3:
      Serial.println("doing nothing!");
      //Test Code
      ignoreLeaveLineCommand = false;
      followingState = true; //Un comment this
      pulse = false;//because int after the first make pulse true
      leaveState = 0;
      break;
  }
}
/*
void remoteISR() 
{
  pulse = true;
}
*/
