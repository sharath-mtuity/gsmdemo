
#ifndef GSMCALLING_H
#define GSMCALLING_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class GSMCalling {
  public:
    GSMCalling(SoftwareSerial *);
    void begin(long);
    void sendATCommand(String command);
    
   private:
    SoftwareSerial *gsmSerial;
    Stream *mySerial;
    
};

#endif
