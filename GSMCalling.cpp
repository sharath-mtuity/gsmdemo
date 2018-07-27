#include <SoftwareSerial.h>
#include <Arduino.h>
#include "GSMCalling.h"


static void serialFlush(Stream *gsmSerial) {
  while (gsmSerial->available() > 0) {
    char t = gsmSerial->read();
    // Serial.write(t);
  }
}

GSMCalling::GSMCalling(SoftwareSerial *serial) {
  gsmSerial = serial;
  mySerial = gsmSerial;
}

void  GSMCalling::begin(long baudRate) {
  gsmSerial -> begin(baudRate);
}

void GSMCalling::sendATCommand(String command) {
  serialFlush(mySerial);
  Serial.println(command);
}

