#include "remoteDecoder.h"

remoteDecoder myDecoder(2);

int decoded;

void setup()
{
  Serial.begin(115200);
  myDecoder.init();
}

void loop()
{
 bool test = myDecoder.detectPulse();
 Serial.println(test); 
  if(test)
  {
    //decoded = myDecoder.decode();
    Serial.println("Pulse Detected!");
    //Serial.println(String("Input Recieved: ") + decoded):
    delay(100);
  }
  
}

