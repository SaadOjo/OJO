#include "remoteDecoder.h"

remoteDecoder myDecoder(4);

int decoded;
bool leaveState = false;

void setup()
{
  Serial.begin(115200);
  myDecoder.init();
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
}

void loop()
{
 bool test = myDecoder.detectPulse();
  if(test)
  {
    leaveState = !leaveState;
    digitalWrite(3,leaveState);
    Serial.println("Pulse Detected!");
    decoded = myDecoder.decode();
    Serial.println(String("Input Recieved: ") + decoded);
    delay(1000);
  }
  
}

