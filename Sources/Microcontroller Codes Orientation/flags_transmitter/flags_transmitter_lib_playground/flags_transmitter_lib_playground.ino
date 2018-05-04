#include "flagsTransmitter.h"
#define LEAVE_PIN 2
#define LAST_PIN  3
flagsTransmitter myFlagsTransmitter(4, 7);

bool leaveState, lastState;
bool transmit;


void setup()
{
  pinMode(LEAVE_PIN, OUTPUT);
  pinMode(LAST_PIN, OUTPUT);

  Serial.begin(115200);
  myFlagsTransmitter.init();



}

void loop()
{
  transmit = false;
  leaveState = digitalRead(LEAVE_PIN);
  lastState = digitalRead(LAST_PIN);

  Serial.println(String("Leave:") + leaveState + "Last State:" + lastState);
  
  if(leaveState && !lastState)
  {
    transmit = true;
    myFlagsTransmitter.setLeaveSignal(HIGH);
    myFlagsTransmitter.setLastSignal(LOW);  
    Serial.println("Last");


  }
  else if(!leaveState && lastState)
  {
    transmit = true;
    myFlagsTransmitter.setLastSignal(HIGH);
    myFlagsTransmitter.setLeaveSignal(LOW);
    Serial.println("Leave");
  
  }
  else
  {
    myFlagsTransmitter.clearFlags();
    Serial.println("Other");
  }

  if(transmit)
  {
    myFlagsTransmitter.transmit();
    Serial.println("Transmitting!");

  }

}

