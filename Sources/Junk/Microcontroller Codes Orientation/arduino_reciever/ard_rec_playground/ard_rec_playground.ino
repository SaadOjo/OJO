#include <Wire.h>
#define SLAVE_ADDR 0x80
unsigned char remoteInfo,avoidInfo;
bool isLastRobot;
bool dataAvailable = false;

void setup()
{
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

void loop()
{
  if(dataAvailable)
  {
  dataAvailable = false;
  Serial.println(String("Remote Info: ") + remoteInfo + " Avoid Info: " + avoidInfo + " is Last: " + isLastRobot);
  remoteInfo = 0;
  avoidInfo = 0;
  isLastRobot = false;
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
