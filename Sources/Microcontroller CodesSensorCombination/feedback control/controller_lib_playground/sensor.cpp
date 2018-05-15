/*
 A custom library written for OJO controller
 Library wrıtten by Syed Saad Saif
 */
#include "sensor.h" 

sensor::sensor(unsigned char debugInfo):_myDirectionSensor(7,6),_mySolarFlag(2,3),_myRpiDecoder(),_myInfraredReceiver(8)
{
 _debugInfo = debugInfo;
}

bool sensor::init(){
//Analog declaration
}
bool sensor::update()
{
  _myDirectionSensor.update();
  _mySolarFlag.update();
  _myRpiDecoder.update();
  _myInfraredReceiver.update();
  //Update the distance sensor as well
}
unsigned char sensor::isVisible()
{
  unsigned char visibility = 0;
  //Visibility Standard
  //0 : No sensor visible
  //1 : All sensors visible
  //2 : Primary sensor visible only
  //3 : Secondary sensor visible only

    switch (_debugInfo)
  {
    case 0: //Both Sensors
        visibility = 1;
        break;

    case 1: //Primary (Camera ect)
        visibility = 1;
      break;

    case 2: //Secondary
      if(_myDirectionSensor.isVisible())
      {
        visibility = 1;
      }
      break;
  }


  //Check visibility using time last transmitted

  return visibility;
  //Update the distance sensor as well
}


unsigned char sensor::getDistance()
{
  unsigned char distance;

  unsigned char piDistance = _myRpiDecoder.getDistance();
  unsigned char irDistance = _myDirectionSensor.getDistance();

  switch (_debugInfo)
  {

    case 0: //Both Sensors
       
      if(_myRpiDecoder.isVisible()&&!_myDirectionSensor.isVisible())
      {
        distance = piDistance;
      }
      if(!_myRpiDecoder.isVisible()&&_myDirectionSensor.isVisible())
      {
        distance = irDistance;
      }
      else
      {
        distance = min(piDistance, irDistance);
      }
      
      break;
      

    case 1: //Primary (Camera ect)
        distance = piDistance;
      break;

    case 2: //Secondary
        distance = irDistance;
      break;
  }
 
  return distance;
}
char sensor::getDirection()
{
  char direction;
  switch (_debugInfo)
  {
    case 0: //Both Sensors
      //Prioritize Camera
      if(_myRpiDecoder.isVisible())
      {
        direction = _myRpiDecoder.getDirection();
      }
      else
      {
        direction = _myDirectionSensor.getDirection();
      }
      break;

    case 1: //Primary (Camera ect)
        direction = _myRpiDecoder.getDirection();
      break;

    case 2: //Secondary
        direction = _myDirectionSensor.getDirection();
      break;
  }
  return direction;
}
unsigned char sensor::getLastOneFlagStatus()
{
  unsigned char lastOneFlag = 0;

  unsigned char solar =   _mySolarFlag.getSolarLastOneFlag();
  unsigned char irFlag =  _myInfraredReceiver.getSignalIdentity();

  switch (_debugInfo)
  {
    case 0: //Both Sensors
      if(solar||irFlag==1)
      {
        lastOneFlag = 1;
      }
      break;

    case 1: //Primary (Camera ect)
      lastOneFlag = solar;
      break;

    case 2: //Secondary
    //get from IR
      if(irFlag == 1)
      {
        lastOneFlag = 1;
      } 
      break;
  }
  return lastOneFlag;
  //this library does not satisfy the update function standard. Make it compliant.
}

char sensor::getOrientation()
{
  char orientation;
  orientation = _myRpiDecoder.getOrientation();
  return orientation;
}

bool sensor::getLeavingFlagStatus()
{ 
  bool leavingFlagStatus = 0;
  unsigned char piFlag = _myRpiDecoder.getLeavingFlagStatus();
  unsigned char irFlag = _myInfraredReceiver.getSignalIdentity();
  
  switch (_debugInfo)
  {
    case 0: //Both Sensors
      if(irFlag == 2 || piFlag)
        { 
          leavingFlagStatus = 1;
        }
      break;

    case 1: //Primary (Camera ect)
        leavingFlagStatus = piFlag;
      break;

    case 2: //Secondary
      if(irFlag == 2)
      {
        leavingFlagStatus = 1;
      }
      break;
  }
  
  return leavingFlagStatus;
}


