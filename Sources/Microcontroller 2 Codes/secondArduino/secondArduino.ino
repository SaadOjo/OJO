#include "collisionDetector.h"
#include <Wire.h>

#define slaveAddress 0x80  
collisionDetector mySensor(7,5,4,7,6,9,8); //echo blue trigger yellow left right back

//Add i2c (added)

char text[5];
boolean nec_ok = 0;
byte  i, nec_state = 0, command, inv_command;
unsigned int address;
unsigned long nec_code;

bool avoidResetSent = false;
bool lastResetSent = false;

unsigned char avoidAction;
bool shouldSend = false;

unsigned char isLastInfoOld,avoidInfoOld,sendByteOld;
unsigned char isLastInfo,remoteInfo,avoidInfo,sendByte;

void setup() {
  Serial.begin(115200);
  TCCR1A = 0;
  TCCR1B = 0;                                    // Disable Timer1 module
  TCNT1  = 0;                                    // Set Timer1 preload value to 0 (reset)
  TIMSK1 = 1;                                    // enable Timer1 overflow interrupt
  attachInterrupt(0, remote_read, CHANGE);       // Enable external interrupt (INT0)
  Wire.begin();
}
void remote_read() {
unsigned int timer_value;
  if(nec_state != 0){
    timer_value = TCNT1;                         // Store Timer1 value
    TCNT1 = 0;                                   // Reset Timer1
  }
  switch(nec_state){
   case 0 :                                      // Start receiving IR data (we're at the beginning of 9ms pulse)
    TCNT1  = 0;                                  // Reset Timer1
    TCCR1B = 2;                                  // Enable Timer1 module with 1/8 prescaler ( 2 ticks every 1 us)
    nec_state = 1;                               // Next state: end of 9ms pulse (start of 4.5ms space)
    i = 0;
    return;
   case 1 :                                      // End of 9ms pulse
    if((timer_value > 19000) || (timer_value < 17000)){         // Invalid interval ==> stop decoding and reset
      nec_state = 0;                             // Reset decoding process
      TCCR1B = 0;                                // Disable Timer1 module
    }
    else
      nec_state = 2;                             // Next state: end of 4.5ms space (start of 562µs pulse)
    return;
   case 2 :                                      // End of 4.5ms space
    if((timer_value > 10000) || (timer_value < 8000)){
      nec_state = 0;                             // Reset decoding process
      TCCR1B = 0;                                // Disable Timer1 module
    }
    else
      nec_state = 3;                             // Next state: end of 562µs pulse (start of 562µs or 1687µs space)
    return;
   case 3 :                                      // End of 562µs pulse
    if((timer_value > 1400) || (timer_value < 800)){           // Invalid interval ==> stop decoding and reset
      TCCR1B = 0;                                // Disable Timer1 module
      nec_state = 0;                             // Reset decoding process
    }
    else
      nec_state = 4;                             // Next state: end of 562µs or 1687µs space
    return;
   case 4 :                                      // End of 562µs or 1687µs space
    if((timer_value > 3600) || (timer_value < 800)){           // Time interval invalid ==> stop decoding
      TCCR1B = 0;                                // Disable Timer1 module
      nec_state = 0;                             // Reset decoding process
      return;
    }
    if( timer_value > 2000)                      // If space width > 1ms (short space)
      bitSet(nec_code, (31 - i));                // Write 1 to bit (31 - i)
    else                                         // If space width < 1ms (long space)
      bitClear(nec_code, (31 - i));              // Write 0 to bit (31 - i)
    i++;
    if(i > 31){                                  // If all bits are received
      nec_ok = 1;                                // Decoding process OK
      detachInterrupt(0);                        // Disable external interrupt (INT0)
      return;
    }
    nec_state = 3;                               // Next state: end of 562µs pulse (start of 562µs or 1687µs space)
  }
}
 
ISR(TIMER1_OVF_vect) {                           // Timer1 interrupt service routine (ISR)
  nec_state = 0;                                 // Reset decoding process
  TCCR1B = 0;                                    // Disable Timer1 module
}
 
void loop() {
  
  //Continue looping until you get a complete signal received
  mySensor.update();
  avoidAction = mySensor.getAvoidAction();
  if(mySensor.robotIsLast())
  {

    isLastInfo = 0b10000000;
  }
  else
  {
    isLastInfo = 0b00000000;
  }

  if(avoidAction)
  {
    Serial.println((String("AA:") + avoidAction));
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
  else
  {
    avoidInfo = 0b00000000;

  }

if(nec_ok)
{                                    // If the mcu receives NEC message with successful
  nec_ok = 0;                                  // Reset decoding process
  nec_state = 0;
  TCCR1B = 0;                                  // Disable Timer1 module
  address = nec_code >> 16;
  command = nec_code >> 8;
  inv_command = nec_code;

  switch(command) 
  {
    case 72:
      Serial.println("LEAVE");
      shouldSend = true;
      remoteInfo = 0b00010000;
      break;
    case 88:
      Serial.println("RES1");
      shouldSend = true;
      remoteInfo = 0b00100000; 
      break;
    case 120:  //Volume Up
      Serial.println("RES2");
      shouldSend = true;
      remoteInfo = 0b00110000;
      break; 
  }
  attachInterrupt(0, remote_read, CHANGE);     // Enable external interrupt (INT0)
}

if(avoidInfoOld != avoidInfo)
{
  shouldSend = true;
} 

if(isLastInfoOld != isLastInfo)
{
  shouldSend = true;
} 

  //First 4 bits for Remote Last 4 for Collision
  if(shouldSend)
  {
    shouldSend = false;
    //Send
    sendByte = isLastInfo | (remoteInfo | avoidInfo);

    //sendByte = 0b00100010; (testing)
    
    Serial.println(sendByte,BIN);
    
    Wire.beginTransmission(slaveAddress);   
    Wire.write(sendByte);                
    Wire.endTransmission(); 
    remoteInfo = 0;
    
  }
    avoidInfoOld = avoidInfo;
    isLastInfoOld = isLastInfo;
  delay(50);
}
