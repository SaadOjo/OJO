#include <Wire.h>
#define slaveAddress 0x80
byte b = 0;
byte remoteInfo, avoidInfo;
void setup()
{
  Wire.begin(slaveAddress);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
}

void loop()
{
  delay(100);
}

void requestEvent() 
{
  Wire.write(b);
}

void receiveEvent(int howMany)
{
  if(Wire.available() != 0)
  {
     for(int i = 0; i<howMany; i++) 
     { 
        b = Wire.read();
        Serial.println(b,HEX);

        switch (b) 
        {
          case 0b1:
          //go forward
            break;
          case 0b10:
          //go left
            break;
          case 0b11:
          //go right
            break;
    }  
   } 
  }
}
