#include <Wire.h>
#include "controller.h"
#include "sensor.h"
#include "flagsTransmitter.h"

#define SLAVE_ADDR 0x80

//i2c variables
unsigned char remoteInfo,avoidInfo;
bool isLastRobot;
bool dataAvailable = false;


robotMotion myMotion(6,5);
flagsTransmitter myFlagsTransmitter(4, 7);

sensor mySensor(1); //Argument is debug info
controller myController(mySensor, myMotion);

// TEST DEFINITIONS
#define ROBOT_TEST_FOLLOW_TIME 5000
/*
 Notes: 
 1) The follow last speed is taken from the propotional control. This will fail to work when the robot is accelerating

 2) Can only handle one leave command (changed not tested)

 3) Lateral Exit uses test conditions for last direction

 4) Have to check next robot leaving case

 5) succeptable to miss i2c recieve

 !!!! Uncompilable there is unwritten function !!!
*/
bool robotVisibilityState = true;
unsigned char leaveState = 0;
bool followingState = true;

bool ignoreLeaveLineCommand = false;

unsigned long int oldTime;
unsigned long int  myTime;

void setup()
{
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  
  myController.setMaxSpeed(100);
  myController.setMinSpeed(30);
  
  myFlagsTransmitter.init();
  myFlagsTransmitter.setLeaveSignal(HIGH);
  myFlagsTransmitter.setLastSignal(HIGH);
  //myFlagsTransmitter.clearFlags();

}

void loop()
{
 // mySensor.update();
 // Serial.println(mySensor.getLeavingFlagStatus());
 //digitalWrite(2,mySensor.getLeavingFlagStatus());
  //updating sensor can have unexpected consequences
  
  //Testing code to display 12c communication
  /*
  if(dataAvailable)
  {
  dataAvailable = false;
  Serial.println(String("Remote Info: ") + remoteInfo + " Avoid Info: " + avoidInfo + " is Last: " + isLastRobot);
  //remoteInfo = 0;
  //avoidInfo = 0;
  //isLastRobot = false;
  } 
  */



  myFlagsTransmitter.setLastSignal(isLastRobot);

if(remoteInfo == 1) //change to take from serial
{
  if(!ignoreLeaveLineCommand)
  {
    
    followingState = false;
    myController.forceFirstLoop();
    remoteInfo = 0;
    ignoreLeaveLineCommand = true;
    Serial.println("Leave command received"); 
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

if(avoidInfo)
{
  Serial.println(String("Avoid Info") + avoidInfo);
  Serial.println("Collision Avoidance");
  myController.avoidCollision(avoidInfo);
  
}
else
{
  switch(followingState)
  {
    case false:
      leaving();
      break;

    case true:
      following();
      break;
  }
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
      Serial.println("Following Robot!");
      if(!myController.followRobot(15)) //does not follow when the robot sees that the robot in front is leaving
      {
        robotVisibilityState = false;
      }
      break;

    case false:
      Serial.println("Finding Robot!");
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
      leaveState = 0;
      break;
  }
}
void receiveEvent(int howMany)
{
  byte b;
  byte lastRobotByte,remoteInfoByte,avoidInfoByte;
  if(Wire.available() != 0)
  {
    dataAvailable = true;
    
     for(int i = 0; i<howMany; i++) 
     { 
        b = Wire.read();
        Serial.println(b,HEX);
        lastRobotByte = b >> 7;
        remoteInfoByte = (b & 0b01111111) >> 4;
        avoidInfoByte = b & 0b00001111;

        if(lastRobotByte) //Kinda Redundant
        {
          isLastRobot = true;
        }
        else
        {
          isLastRobot = false;
        }

        switch (remoteInfoByte)//Intentionally Redundant
        {
          case 0b1:
            remoteInfo = 1;
            break;
          case 0b10:
            remoteInfo = 2;
          //go left
            break;
          case 0b11:
            remoteInfo = 3;
          //go right
            break;
        }
        switch (avoidInfoByte) 
        {
          case 0b0:
            avoidInfo = 0;
            break;
            
          case 0b1:
            avoidInfo = 1;
            break;
          case 0b10:
            avoidInfo = 2;
          //go left
            break;
          case 0b11:
            avoidInfo = 3;
          //go right
            break;
        }
    } 
  }
}
