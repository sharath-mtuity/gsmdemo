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

boolean GSMCalling::SendAT(String ATCommand, const char* exptReply, uint32_t timeout, int retry) {
 int itr = 0;
  serialFlush(mySerial); /*Flush all the pending inputs in serial buffer*/
  while (itr++ < retry)
  { /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
#if (DEBUG == 1)
    Serial.print(F("Sending "));
    Serial.println(F(ATCommand));
#endif
    mySerial->println(ATCommand); /*Send AT command to the GSM RX pin*/
    boolean status = waitResponse(exptReply, timeout);
    if (status == true)
    {
      return true;
    }
  }
  return false;
}

boolean GSMCalling::waitResponse(const char* exptReply, uint32_t timeout) {
  String inputString = "";
  inputString = readReply(timeout);
#if (DEBUG == 1)
  Serial.println(F(inputString));
#endif
  boolean response = checkForExptReplyinRcvdString(inputString, exptReply);
  return response;
}

boolean GSMCalling::checkForExptReplyinRcvdString(String recvdString, const char* exptReply)
{
  if (strstr(recvdString.c_str(), exptReply) != 0)
  {
#if (DEBUG == 1)
    Serial.println(F("Got Correct Reply"));
#endif
    recvdString = "";
    return true;
  }
  else
  {
#if (DEBUG == 1)
    Serial.println(F("Got ERROR"));
#endif
    recvdString = "";
    return false;
  }

}

String GSMCalling::readReply(uint32_t timeout){
  uint32_t previousTime = millis();
  String receivedString = "";
  while (millis() - previousTime < timeout)
  {
    if (mySerial->available())
    {
      char inChar = (char)mySerial->read();
      if ((inChar != '\n') && (inChar != '\r'))
      { /*Append data till enter character received*/
        receivedString += inChar;
      }
      else
      {
        return receivedString;
      }
    }
  }

}


boolean GSMCalling::enableCallerInfo() {
  boolean status = SendAT("AT+CLIP=1", "OK", 1000, 1 );
  Serial.print(F("enableCallerInfo: "));
  Serial.println((status));
  return status;
}


boolean GSMCalling::checkNetworkStatus() {
  boolean status = SendAT("AT+CREG?", "+CREG: 0,1", 1000, 1);
  Serial.print(F("checkNetworkStatus:::"));
  Serial.println((status));
  return status;
}

void GSMCalling::setAutoAnswer(int num) {
  String cmd = "ATS0=";
  String cmd2 = cmd+num;
   boolean status = SendAT(cmd2, "OK", 1000, 1);
  Serial.print(F("setAutoAnswer :::"));
  Serial.println((status));
  
}
