#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial serialOut(3, 2);
Stream *gsmSerial;


const char phone_number[11] = "9014444124";
const long BAUD_RATE = 9600;
bool isCallInitiated = false;   //to check wheather user initiated the call by clicking on the push button


#define PUSH_BUTTON_PIN 9

void setup() {
  Serial.begin(BAUD_RATE);
  serialOut.begin(9600);

  pinMode(PUSH_BUTTON_PIN, INPUT);

  Serial.print("setup") ;
//  gsmSerial = &serialOut;

  //  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON_PIN), &handleStartButtonPress, CHANGE);

}

void loop() {
  if ( digitalRead(PUSH_BUTTON_PIN) == LOW && isCallInitiated == false) {
    Serial.println( "Switch on*******");
    isCallInitiated = true;
    makeCall();


  }


}
void serialFlush(Stream *gsmSerial) {
  while (gsmSerial->available() > 0) {
    char t = gsmSerial->read();
    Serial.write(t);
  }
}
void makeCall() {
  Serial.println( "Making call*******");
  //  serialFlush(gsmSerial);
  if (isCallInitiated == false) {
    return;
  }
  char cmd[20];
  sprintf((char*)cmd, "%s%s%s", "ATD", phone_number, ";");
  Serial.println(cmd);
  serialOut.println(cmd);



}



void sendAT(String ATCommand, const char* exptReply, uint32_t timeout, int retry, uint8_t noOflines) {
  int itr = 0;
  serialFlush(gsmSerial); /*Flush all the pending inputs in serial buffer*/
  while (itr++ < retry) { /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
#if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
#endif
    serialOut.println(ATCommand); /*Send AT command to the GSM RX pin*/
    //    boolean status = waitResponse(exptReply, timeout, noOflines);
    /*if (status == true)
      {
      return true;
      }
      }
      return false;*/
  }
}

void handleStartButtonPress() {
  Serial.print("handleStartButtonPress*****") ;
}

