#include <Wire.h>
#define slaveAddress 0x80
byte b = 0;
void setup()
{
  Wire.begin(slaveAddress);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
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
     for(int i = 0; i<howMany; i++) { 
        b = Wire.read();
        Serial.print(0b11110000);

        switch (b) {

          case 0b00000001:
          //go forward
          break;
          case 0b00000010:
          //go left
          break;
          case 0b00000011:
          //go right
          break;
          case 0b00010000:
          //leave command
          break;
   
          
    }  
   } 
  }
}
