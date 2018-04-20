#include "flagsTransmitter.h"

flagsTransmitter myFlagsTransmitter(2, 3);


void setup()
{
  Serial.begin(115200);
  myFlagsTransmitter.init();
}

void loop()
{
  myFlagsTransmitter.setLeaveSignal(HIGH);
  myFlagsTransmitter.setLastSignal(HIGH);
  delay(100);
  myFlagsTransmitter.setLeaveSignal(LOW);
  myFlagsTransmitter.setLastSignal(HIGH);
  delay(100);
  myFlagsTransmitter.clearFlags();
  delay(1000);
}

