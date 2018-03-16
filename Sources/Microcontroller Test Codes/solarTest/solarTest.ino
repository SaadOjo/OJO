bool pinState; //Potentially wasting one bit
bool ledState;

#define ON_TIME 1000 

unsigned long int eventTime;

void setup() {
pinMode(13,OUTPUT);
pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
pinState = digitalRead(3);

  if(pinState)
  {
    ledState = true;
    eventTime = millis();
  }
  if(ledState)
  {
    if(millis() - eventTime > ON_TIME)
    {
      ledState = false;
    }
  }
  
digitalWrite(13, ledState);

delay(100);
  
}
