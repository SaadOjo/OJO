//Arduino I2C code for the master
#include <Wire.h>
#define slaveAddress 0x80   

void setup() {
  
    Wire.begin();
    Serial.begin(115200);
    
}

byte b = 0; 

void loop() {

    b = random(0,255);
    Wire.beginTransmission(slaveAddress);   
    Wire.write(b);                
    Wire.endTransmission();   
    delay(100);
    /*
    Wire.requestFrom(slaveAddress, 1);

    int howMany = Wire.available();
    for(int i = 0; i<howMany; i++) {
    
          b = Wire.read();
          Serial.print(b,BIN);
    }
    */
}
