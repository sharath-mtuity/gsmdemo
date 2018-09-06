
#ifndef GSMCALLING_H
#define GSMCALLING_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class GSMCalling {
  public:
    GSMCalling(SoftwareSerial *);
    void begin(long);
    boolean SendAT(String ATCommand, const char* exptReply, uint32_t timeout, int retry);
    boolean  enableCallerInfo();
    boolean checkNetworkStatus();
    void setAutoAnswer(int num);

   private:
    SoftwareSerial *gsmSerial;
    Stream *mySerial;
    boolean waitResponse(const char* exptReply, uint32_t timeout);
    boolean checkForExptReplyinRcvdString(String recvdString, const char* exptReply);
    String readReply(uint32_t timeout);

    
};

#endif
