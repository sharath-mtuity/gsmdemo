#include <SoftwareSerial.h>
#include "ElementzGSM.h"
#include "GSMCalling.h"

SoftwareSerial serialOut(3,2);
ElementzGSMshield GSM(&serialOut);
//GSMCalling gsmCall(&serialOut);
char phone_number[11] ="9014444124";
const long BAUD_RATE = 2000000;
const int AUTO_ANSWER_DURATION = 2;
#define pin_LED 13
void setup() {
 
  Serial.begin(BAUD_RATE);
  serialOut.begin(BAUD_RATE);
  GSM.begin(9600);

  boolean status = GSM.enableCallerInfo();
  delay(2000);
  bool networkstatus = GSM.checkNetworkStatus();
  delay(2000);

  if( networkstatus == false) {
    Serial.println("Some issue with mobile carrier,plese check the sim and try again");
  }
  else {
  }
//      GSM.makeCall(phone_number);//number const char type
  GSM.setAutoAnswer(AUTO_ANSWER_DURATION);
  delay(2000);
  Serial.print("serial available");
 
//  Serial.println(cmd2);
  
}

void loop() {
  // put your main code here, to run repeatedly:
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
