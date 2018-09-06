#include <SoftwareSerial.h>
#include "ElementzGSM.h"
#include "GSMCalling.h"

SoftwareSerial serialOut(3,2);
/*ElementzGSMshield*/ GSMCalling GSM(&serialOut);
//GSMCalling gsmCall(&serialOut);
char phone_number[11] = "9398703484";//"9014444124";
const long BAUD_RATE = 9600;
const int AUTO_ANSWER_DURATION = 2;
bool isStarted = false;       // to check wheather app is already started or not

#define pin_LED 13


void setup() {
    Serial.begin(BAUD_RATE);

  Serial.print(F("isStarted: "));
  Serial.println((isStarted));
 if (!isStarted) {
  isStarted = true;
//  serialOut.begin(BAUD_RATE);
  GSM.begin(9600);

  boolean status = GSM.enableCallerInfo();
  delay(2000);
  bool networkstatus = GSM.checkNetworkStatus();
  delay(2000);

  if( networkstatus == false) {
    Serial.println(F("Some issue with mobile carrier,plese check the sim and try again"));
  }
  else {
  }
  GSM.setAutoAnswer(AUTO_ANSWER_DURATION);
  delay(2000);
  Serial.print(F("serial available"));
//  GSM.makeCall(phone_number);//number const char type
 } else {
  Serial.println(F("****** AUTO RESTARTED *******"));
 }
  

  
}

void loop() {
  digitalWrite(pin_LED,HIGH);
  delay(250);
  digitalWrite(pin_LED,LOW);
  delay(250);
  
  if (serialOut.available()) {
    Serial.write(serialOut.read());
  }
  while(Serial.available())
    {
      serialOut.write(Serial.read());
    }
    serialOut.println();
}
