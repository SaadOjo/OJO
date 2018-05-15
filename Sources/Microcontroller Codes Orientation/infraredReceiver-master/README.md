# infraredReceiver Library
**A simple library to receive a simplified version of the IR remote protocol**

## Use case scenario
The Library is intended to be used in time critical systems where the programmer can not afford to lock hardware resources. For example, the simple protocol will allow the use of a single microcontroller for realtime controllers. A feedback controller in a drone can be simultaneously used to identify basic commands signals.

Please note that this Library is expected to be used with the related **infraredTransmitter** library which is designed to handle the transmission of the signal.

The reciever can be connected to any __Digital Pin__ of the arduino.

## Initialising the Transmitter
```
infraredReciever myReciever(2);
myReciever.init();
```

## Library Methods

**to detect the signal:**

detect functions returns 0 when no signal is detected
returns non zero values for other signal types

```
myReciever.detect(); // must be called on each loop
```


