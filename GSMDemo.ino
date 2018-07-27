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
  delay(2000);
  Serial.begin(9600);
  GSM.begin(9600);
//  gsmCall.begin(19200);

boolean status = GSM.enableCallerInfo();
delay(2000);
Serial.print("Status:"+status);

  pinMode(pin_LED,OUTPUT);
  Serial.write("In start");

  Serial.println("Calling First Number");
//  gsmCall.sendATCommand("AT9014444124;");
  delay(2000);
    Serial.println("Command sent");

//  GSM.makeCall(phone_number);//number const char type
  delay(20000);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_LED,HIGH);
//    Serial.write("High");

  delay(250);
  digitalWrite(pin_LED,LOW);
//      Serial.write("low");

  delay(250);
}
