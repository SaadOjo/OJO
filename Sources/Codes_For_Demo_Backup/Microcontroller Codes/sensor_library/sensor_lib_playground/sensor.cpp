/*
 A custom library written for OJO controller
 Library wrıtten by Syed Saad Saif
 */
#include "sensor.h" 

sensor::sensor(unsigned char debugInfo):_mySensor(1),_myDirectionSensor(2,3),_mySolarFlag(7,8),_myRpiDecoder()
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

  switch (_debugInfo)
  {
    case 0: //Both Sensors
      break;

    case 1: //Primary (Camera ect)
        distance = _myRpiDecoder.getDistance();
      break;

    case 2: //Secondary
        distance = _myDirectionSensor.getDistance();
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
  unsigned char getSolarLastOneFlag;

  switch (_debugInfo)
  {
    case 0: //Both Sensors
      break;

    case 1: //Primary (Camera ect)
      getSolarLastOneFlag = _mySolarFlag.getSolarLastOneFlag();
      break;

    case 2: //Secondary
    //get from IR
      break;
  }
  return getSolarLastOneFlag;
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
  bool leavingFlagStatus;
  
  switch (_debugInfo)
  {
    case 0: //Both Sensors
      break;

    case 1: //Primary (Camera ect)
        leavingFlagStatus = _myRpiDecoder.getLeavingFlagStatus();
      break;

    case 2: //Secondary
        //get from IR
      break;
  }
  
  return leavingFlagStatus;
}


