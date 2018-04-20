
/*
 Controller library for EE493 Convoy Design Project.
 Uses external PID controller libraries

 Written by Syed Saad Saif
 11/25/2017
 */
#include "Arduino.h"
#include "controller.h"

controller::controller(sensor &sensor, robotMotion &motion):_mySensor(&sensor), _myMotion(&motion)
{
  
}
 bool controller::setMaxSpeed(unsigned char maxSpeed)
{
  _maxSpeed = maxSpeed;
}
 bool controller::setMinSpeed(unsigned char minSpeed)
{
  _minSpeed = minSpeed;
}
bool controller::followRobot(int referenceDistance)
{
  bool status;
  bool robotInFrontLeaving = false;

  if(leavingRobotObservedFirstTime && robotInFrontLeaving)
  {
    Serial.println("Observation: Front robot is leaving.");
    leavingRobotObservedFirstTime = false;
    maintainVelocityBool = true;
    maintainVelocityStartTime = millis();
  }

  if(maintainVelocityBool)
  {
    _maintainVelocity();
    
    if((millis() - maintainVelocityStartTime) > MAINTAIN_VELOCITY_TIME)
    {
      maintainVelocityBool = false;
    }
    status = true;
  }
  else
  {
    status = maintainDistance(referenceDistance);
  }
  return status;
}
bool controller::forceFirstLoop()
{
  _maneuverFirstLoop = true;
}
bool controller::forceMotors(unsigned char speed, unsigned char direction)
{
  _myMotion->setSpeed(speed); 
  _myMotion->setDirection(direction); 
  _myMotion->run(); 
}
bool controller::maintainDistance(int referenceDistance)
{
  bool Status = true;
  
  _mySensor -> update(); //New standard added. Other rudamentary sensor libs should conform to this standard
  //_relativeDistance = getAverageDistance();
  _relativeDistance = _mySensor -> getDistance();
  //Serial.println(String("Distance from new sensor: ") + _relativeDistance);
  //_relativeDistance = 100; //Just to force the robot to keep moving (TEST)
  _relativeDirection = _mySensor -> getDirection();

 // TEST CODE
 /*
  if(_relativeDirection<-1)
  {
    _relativeDirection = -70;
  }
  else if(_relativeDirection>1)
  {
    _relativeDirection = 70;
  }
  else
  {
    _relativeDirection = 0;
  }
  */
  
  _propotionalControl = _K_p *  (_relativeDistance - referenceDistance);

  _propotionalControl += _controllerBias; //Add bias term for steady state
 /*
  //Condition Output
  if(_propotionalControl>255)
  {
    _propotionalControl = 255;
  }
  if(_propotionalControl<0)
  {
    _propotionalControl = 0;
  }
  */

  _propotionalControl = posSaturate(_propotionalControl,255);
  _propotionalControl = map(_propotionalControl,0,255,0,100);
  _propotionalControl = posSaturate(_propotionalControl,_maxSpeed);
  
  if(_propotionalControl<_minSpeed)
  {
    _propotionalControl = 0;
  }

  //Check if front robot is there or not

  if(!(_mySensor -> isVisible()))
  {
    _propotionalControl = 0;
    _maneuverFirstLoop = true;
    Status = false;
  }
  
  Serial.print(String("The relative distance is: ") + _relativeDistance);
  Serial.println(String(" SPD:") + _propotionalControl);
  Serial.println(String(" DIR:") + _relativeDirection);
  _myMotion->setSpeed(_propotionalControl); //Have to scale
  _lastSpeed = _propotionalControl;
  _myMotion->setDirection(_relativeDirection); //Have to scale
  _myMotion->run();

  return Status;
}
int controller::getAverageDistance()
{
  int averageDistance = 0;
  
  _relativeDistanceArray[_ringCounter%AVERAGE_SAMPLES] = _mySensor -> getDistance(); //Overflow possible
  
  for (int i = 0 ; i<AVERAGE_SAMPLES;i++ )
  {
    averageDistance += _relativeDistanceArray[i];
  }
  _ringCounter++;
  return averageDistance/AVERAGE_SAMPLES;
  
}
bool controller::findMarker()
{
  bool Status = false;
  bool turnDirection = false;

  if(_maneuverFirstLoop)
  {   _maneuverFirstLoop = false;
      _maneuverStartTime = millis();
      _turnModifier = false;
      Serial.println("First Loop, Timer Started");
      Serial.println(String("Turn Modifier: ") + _turnModifier);
      
     if(_mySensor -> getDirection() > 0)
    {
      _lastDirectionSign = RIGHT;
    }
    else
    {
      _lastDirectionSign = LEFT;
    }
    
  }
    _mySensor -> update();

  //Do Stuff here
  _myMotion->setSpeed(100);
  
  unsigned char eventSecond = ((millis() - _maneuverStartTime)/1000) % FIND_ROBOT_SWITCH_TIME;
  Serial.println(eventSecond);
  
  if(eventSecond == 0)
  {
    _first = true;
  }
  
  if((eventSecond == (FIND_ROBOT_SWITCH_TIME - 1)) && _first)
  {
    _turnModifier = 1 - _turnModifier;
    Serial.println("Modifer Modified ");
    _first = false;
  }

  Serial.println(String("Turn Modifier: ") + _turnModifier);
  turnDirection =  _turnModifier ^ _lastDirectionSign;
  Serial.println(String("turnModifier: ") +  _turnModifier);


  if(turnDirection)
  {
    _myMotion->setDirection(80);
    Serial.println("Right");
  }
  else
  {
    _myMotion->setDirection(-80);
    Serial.println("Left");
  }
  
  _myMotion->run();
  
  if(_mySensor -> isVisible())
  {
    Status = true;
    _maneuverFirstLoop = true; 
  }

  return Status;
}

bool controller::lateralExit()
{
  bool Status = false;
  bool leaveDirection = false;
  unsigned long int processTime = _maneuverTime - _maneuverStartTime;
  _maneuverTime = millis();
  
  if(_maneuverFirstLoop)
  {   _maneuverFirstLoop = false;
      _maneuverStartTime = _maneuverTime;

      
     if(_mySensor -> getDirection() > 0)
    {
      _lastDirectionSign = RIGHT;
    }
    else
    {
      _lastDirectionSign = LEFT;
    }
    //Set test parameters
    _lastDirectionSign = LEFT;  
    _leaveDirection = !_lastDirectionSign;
    
  }
    //_mySensor -> update();

  //Do Stuff here

  if((_maneuverTime - _maneuverStartTime)> LATERAL_LEAVE_TURN_TIME)
  {
    if((_maneuverTime - _maneuverStartTime)> (LATERAL_EXIT_TIME + LATERAL_LEAVE_TURN_TIME))
    {
      _myMotion->setSpeed(100);
      if(!_leaveDirection)//Return Back
      {
        _myMotion->setDirection(80);
        Serial.println("Right");
      }
      else
      {
        _myMotion->setDirection(-80);
        Serial.println("Left");
      }
    }
    else
    {
      _myMotion->setDirection(0);
      _myMotion->setSpeed(_lastSpeed); 
      Serial.println("Straightening!");
    }

  }
  else
  {
    if(_leaveDirection)
    {
      _myMotion->setDirection(80);
      Serial.println("Right");
    }
    else
    {
      _myMotion->setDirection(-80);
      Serial.println("Left");
    }
    _myMotion->setSpeed(100);
  }
  

  if((_maneuverTime - _maneuverStartTime) > (LATERAL_EXIT_TIME + 2*LATERAL_LEAVE_TURN_TIME))
  {
    _myMotion->setDirection(0);
    Status = true;
    _maneuverFirstLoop = true; 
  }

  _myMotion->run();
  
  return Status;
  
}

bool controller::moveBack()
{
  bool Status = false;
  unsigned long int processTime = _maneuverTime - _maneuverStartTime;
  bool markerFound = false;
  _maneuverTime = millis();
  
  if(_maneuverFirstLoop)
  {   _maneuverFirstLoop = false;
      _maneuverStartTime = _maneuverTime;
    
  }
    _mySensor -> update();
    markerFound =  _mySensor -> getLastOneFlagStatus(); // not created yet
  //Do Stuff here

    if(markerFound)
  {
    _myMotion->setDirection(0);
    _myMotion->setSpeed(0);
    Status = true;
    _maneuverFirstLoop = true; 
  }
  else
  {
    _myMotion->setDirection(0);
    _myMotion->setSpeed(10); 
    Serial.println("Going Back.");
  }

  _myMotion->run();
  
  return Status;
  
}

bool controller::rejoin()
{
  bool Status = false;
  unsigned long int processTime = _maneuverTime - _maneuverStartTime;
  bool markerFound = false;
  bool rejoinDirection = !_leaveDirection;
  _maneuverTime = millis();
  
  if(_maneuverFirstLoop)
  {   _maneuverFirstLoop = false;
      _maneuverStartTime = _maneuverTime;
  }

 //Do Stuff here

  if((_maneuverTime - _maneuverStartTime)> REJOIN_LEAVE_TURN_TIME)
  {
    if((_maneuverTime - _maneuverStartTime)> (REJOIN_ENTRY_TIME + REJOIN_LEAVE_TURN_TIME))
    {
      _myMotion->setSpeed(100);
      if(!rejoinDirection)//Return Back
      {
        _myMotion->setDirection(80);
        Serial.println("Right");
      }
      else
      {
        _myMotion->setDirection(-80);
        Serial.println("Left");
      }
    }
    else
    {
      _myMotion->setDirection(0);
      _myMotion->setSpeed(_lastSpeed); 
      Serial.println("Straightening!");
    }

  }
  else
  {
    if(rejoinDirection)
    {
      _myMotion->setDirection(80);
      Serial.println("Right");
    }
    else
    {
      _myMotion->setDirection(-80);
      Serial.println("Left");
    }
    _myMotion->setSpeed(100);
  }
  

  if((_maneuverTime - _maneuverStartTime) > (REJOIN_ENTRY_TIME + 2*REJOIN_LEAVE_TURN_TIME))
  {
    _myMotion->setDirection(0);
    Serial.println("Waiting for visibility marker!");
  }


  _mySensor -> update();
  if(_mySensor -> isVisible())
  {
    Status = true;
    _maneuverFirstLoop = true; 
  }
  

  _myMotion->run();
  
  return Status;
  
}

void controller::_maintainVelocity()
{
  Serial.println("Maintaining Velocity.");
  _myMotion->setDirection(_relativeDirection); //Set to what it was before
  _myMotion->setSpeed(_lastSpeed); 
  _myMotion->run(); //Should be the last direction not sure
  
  
}


