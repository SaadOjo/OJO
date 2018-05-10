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

sensor mySensor(2); //Argument is debug info
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
bool laserAllowed = true;
bool ignoreLeaveLineCommand = false;

unsigned long int oldTime;
unsigned long int  myTime;

void setup()
{
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  
  myController.setMaxSpeed(100);
  myController.setMinSpeed(0);
  
  myFlagsTransmitter.init();
  myFlagsTransmitter.clearFlags();

}

void loop()
{
  
handleRemote();


avoidInfo = 0; //Ignoring avoid info
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
      myFlagsTransmitter.setLastSignal(LOW);
      myFlagsTransmitter.setLeaveSignal(HIGH);
      myFlagsTransmitter.transmit();
      break;

    case true:
      if(laserAllowed)
      {
        if(isLastRobot)
        {
          myFlagsTransmitter.setLastSignal(HIGH);
          myFlagsTransmitter.setLeaveSignal(LOW);
          myFlagsTransmitter.transmit();
        }
        else
        {
           myFlagsTransmitter.clearFlags();
        }
      }
      else
      {
        myFlagsTransmitter.clearFlags();
      }
      following();
      break;
  }
}


  myTime = millis();
  Serial.println(String("Loop Tme: ") + (myTime - oldTime));
  oldTime = myTime;
  delay(20);

}

void handleRemote(void)
{
  switch(remoteInfo)
  {
    case 1:
      if(!ignoreLeaveLineCommand)
      {
        
        followingState = false;
        myController.forceFirstLoop();
        ignoreLeaveLineCommand = true;
        Serial.println("Leave command received"); 
      }
      break;
    case 2:
      laserAllowed = !laserAllowed;
      Serial.println("Laser protection toggled"); 
      
      break;
    case 3:
      break;
    
  }
  if(remoteInfo)
  {
    remoteInfo = 0;
  }
  
}

void following(void)
{   
 
   switch(robotVisibilityState)
  {
    case true:
      Serial.println("Following Robot!");
      if(!myController.followRobot(17)) //does not follow when the robot sees that the robot in front is leaving
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
