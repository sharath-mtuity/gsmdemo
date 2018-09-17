#include <SoftwareSerial.h>
#include "ElementzGSM.h"
#include "GSMCalling.h"

SoftwareSerial serialOut(3, 2);
ElementzGSMshield /*GSMCalling */GSM(&serialOut);
//GSMCalling gsmCall(&serialOut);
char phone_number[11] = "9398703484";//"9014444124";
const long BAUD_RATE = 9600;
const int AUTO_ANSWER_DURATION = 1;
bool isStarted = false;       // to check wheather app is already started or not
bool isCallInitiated = false;   //to check wheather user initiated the call by clicking on the push button

#define pin_LED 13
#define START_BUTTON_PIN 9



void setup() {
  Serial.begin(BAUD_RATE);

  Serial.print(F("isStarted: "));
  Serial.println((isStarted));
  if (!isStarted) {
    isStarted = true;
    //  serialOut.begin(BAUD_RATE);
//    serialOut.begin(9600);
    GSM.begin(9600);
    pinMode(START_BUTTON_PIN, INPUT);

    boolean status = GSM.enableCallerInfo();
    delay(2000);
    bool networkstatus = GSM.checkNetworkStatus();
    delay(2000);

    if ( networkstatus == false) {
      Serial.println(F("Some issue with mobile carrier,plese check the sim and try again"));
    }
    else {
    }
    GSM.setAutoAnswer(AUTO_ANSWER_DURATION);
    delay(2000);
    Serial.println(F("serial available"));
  } else {
    Serial.println(F("****** AUTO RESTARTED *******"));
  }



}

void loop() {
  String reply = "";
//  #if (DEBUG == 1)
//  if (!reply.equals(" \n")) {
     Serial.println(reply);
//  }
//  #endif
  
   /* while(serialOut.available()) {
      Serial.println(GSM.readReply(1000, 1));
    }
*/
    if(Serial.available()) {
      GSM.SendAT(Serial.readString());
//      serialOut.write(Serial.read());
    }

  if (isCallInitiated == false && digitalRead(START_BUTTON_PIN) == false ) {
    Serial.print(F("Call initiated"));
    isCallInitiated = true;
    GSM.makeCall(phone_number);
  }
  reply = GSM.readReply(1000, 1);
  if (reply.indexOf("RING") > 0) {
    // incoming call, call shouldnt be initiated
    isCallInitiated = false;
    Serial.print(F("Ringinggg.... "));

  }


  if (isCallInitiated == true) {
//    String reply = GSM.readReply(1000, 1);
    reply = GSM.readReply(1000, 1);
    if (reply.indexOf("NO CARRIER") > 0) {
      //call disconnected
      Serial.print(F("call disconnected "));
      isCallInitiated = false;
    }
  }
  digitalWrite(pin_LED, HIGH);
  delay(250);
  digitalWrite(pin_LED, LOW);
  delay(250);


 /* if (Serial.available())
  {
      Serial.println(F("to gsm"));
    while(Serial.available()) {
      serialOut.write(Serial.read());
    }
    Serial.println(F("to gsm end"));
  } */

}
