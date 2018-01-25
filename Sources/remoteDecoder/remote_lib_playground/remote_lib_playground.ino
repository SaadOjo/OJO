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
  if(test)
  {
    Serial.println("Pulse Detected!");
    decoded = myDecoder.decode();
    //Serial.println(String("Input Recieved: ") + decoded);
    delay(1000);
  }
  
}

