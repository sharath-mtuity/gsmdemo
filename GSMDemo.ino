#include <SoftwareSerial.h>
#include "ElementzGSM.h"
#include "GSMCalling.h"

SoftwareSerial serialOut(3,2);
ElementzGSMshield GSM(&serialOut);
//GSMCalling gsmCall(&serialOut);
char phone_number[11] ="9014444124";

#define pin_LED 13
void setup() {
  // put your setup code here, to run once:
  //delay(2000);
  Serial.begin(9600);
  serialOut.begin(9600);
  GSM.begin(9600);

  boolean status = GSM.enableCallerInfo();
  delay(2000);
//  Serial.print("Status:"+status);

  //pinMode(pin_LED,OUTPUT);
  //Serial.write("In start");
  bool networkstatus = GSM.checkNetworkStatus();
  delay(2000);

  if( networkstatus == false) {
    Serial.println("Some issue with mobile carrier,plese check the sim and try again");
  }
  else {
      GSM.makeCall(phone_number);//number const char type

  }

  delay(20000);
  Serial.print("serial available");
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_LED,HIGH);
//    Serial.write("High");

  delay(250);
  digitalWrite(pin_LED,LOW);
//      Serial.write("low");

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
