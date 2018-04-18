#include "IRLibAll.h"
#include "collisionDetector.h"
#include <Wire.h>

#define slaveAddress 0x80  
IRrecvPCI myReceiver(2);
collisionDetector mySensor(4,5,6,7,8,9,10);
IRdecode myDecoder;   

//Add i2c (added)

unsigned char avoidAction;
bool shouldSend = false;

unsigned char isLastInfo,remoteInfo,avoidInfo,sendByte;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  myReceiver.enableIRIn(); // Start the receiver
}
 
void loop() {
  //Continue looping until you get a complete signal received
  avoidAction = mySensor.getAvoidAction();
  if(mySensor.robotIsLast())
  {
    shouldSend = true;
    isLastInfo = 0b10000000;
  }
  else
  {
    isLastInfo = 0b00000000;
  }

  if(avoidAction)
  {
    Serial.println((String("AA:") + avoidAction));
    shouldSend = true;
    switch(avoidAction)
    {
      case 1:
        avoidInfo = 0b00000001;
        break;
  
      case 2:
        avoidInfo = 0b00000010;
        break;
  
      case 3:
        avoidInfo = 0b00000011;
        break;
    }
  }

    
  if (myReceiver.getResults()) 
  {
    myDecoder.decode();           //Decode it
    if (myDecoder.protocolNum == NEC) 
    {
      switch(myDecoder.value) 
      {
        case 0x1FE48B7:
          Serial.println("LEAVE");
          shouldSend = true;
          remoteInfo = 0b00010000;
          break;
        case 0x1FE58A7:
          Serial.println("RES1");
          shouldSend = true;
          remoteInfo = 0b00100000; 
          break;
        case 0x1FE7887:  //Volume Up
          Serial.println("RES2");
          shouldSend = true;
          remoteInfo = 0b00110000;
          break; 
      }
    }
    myReceiver.enableIRIn();      //Restart receiver
  }

  //First 4 bits for Remote Last 4 for Collision
  if(shouldSend)
  {
    shouldSend = false;
    //Send
    sendByte = isLastInfo | remoteInfo | avoidInfo;
    Serial.println(sendByte,BIN);
    
    Wire.beginTransmission(slaveAddress);   
    Wire.write(sendByte);                
    Wire.endTransmission(); 
    
    avoidInfo = 0;
    remoteInfo = 0;
    isLastInfo = 0;
  }
  delay(100);
}
