#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial serialOut(3, 2);
Stream *gsmSerial;


const char phone_number[11] = "9014444124";
const long BAUD_RATE = 9600;
bool isCallInitiated = false;   //to check wheather user initiated the call by clicking on the push button
char cmd[20];
char expected[10];
char failure[10];
char failure1[10];

#define PUSH_BUTTON_PIN 9
#define PUSH_BUTTON_HIGH_PIN 11


void setup() {
  Serial.begin(BAUD_RATE);
  serialOut.begin(9600);

  pinMode(PUSH_BUTTON_HIGH_PIN, OUTPUT);
  digitalWrite(PUSH_BUTTON_HIGH_PIN, HIGH);

  pinMode(PUSH_BUTTON_PIN, INPUT);

  Serial.print("setup") ;
  enableCalledID();
  //  gsmSerial = &serialOut;

  //  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON_PIN), &handleStartButtonPress, CHANGE);

}
void enableCalledID() {
  sprintf((char*)cmd, "%s", "AT+CLIP=1");
  sprintf((char*)expected, "%s", "OK");
  sprintf((char*)failure, "%s", "ERROR");
  sprintf((char*)failure1, "%s", "ERROR");

  int8_t result = sendATcommand2(cmd, expected  , failure, failure1, 1000);
  Serial.print(F("Called ID enabled: "));
  Serial.println(result);

}

String readReply(uint32_t timeout)
{
  uint32_t previousTime = millis();
  String receivedString = "";
  while (millis() - previousTime < timeout)
  {
    if (serialOut.available())
    {
      char inChar = (char)serialOut.read();
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
String response = "";
void loop() {
  //  Serial.println(digitalRead(PUSH_BUTTON_PIN));
  if ( digitalRead(PUSH_BUTTON_PIN) == LOW && isCallInitiated == false) {
    Serial.println( "Switch on*******");
    isCallInitiated = true;
    makeCall();
  }
  //  serialOut.flush();
  //  response = readReply(2000);

  if (isCallInitiated == true) {
    if (response.indexOf("NO CARRIER") > 0) {
      //call disconnected
      Serial.print(F("call disconnected "));
      isCallInitiated = false;
    }
  }

  if (response.indexOf("RING") > 0) {
    // incoming call, call shouldnt be initiated
    isCallInitiated = false;
    Serial.print("Ringinggg.... ");
  }
  //  /*
  while (serialOut.available()) {
    Serial.write(serialOut.read());
  }

  while (Serial.available())
  {
    serialOut.write(Serial.read());
  }
  //    */

}
void serialFlush(SoftwareSerial gsmSerial) {
  while (gsmSerial.available() > 0) {
    char t = gsmSerial.read();
    Serial.write(t);
  }
}
void sendComamnd(char* cmd) {
  Serial.println(cmd);
  serialOut.println(cmd);
}

void makeCall() {
  if (isCallInitiated == false) {
    return;
  }

  Serial.println( "Making call*******");


  sprintf((char*)cmd, "%s%s%s", "ATD", phone_number, ";");
  sprintf((char*)expected, "%s", "OK");
  sprintf((char*)failure, "%s", "NO CARRIER");
  sprintf((char*)failure1, "%s", "ERROR");


  //  sendComamnd(cmd);
  int8_t result = sendATcommand2(cmd, expected  , failure, failure1, 1000);
  Serial.print("Calling result: ");
  Serial.println(result);
  if (result == 1 ) {
    isCallInitiated = true;
  } else {
    isCallInitiated = false;

  }


}


int8_t sendATcommand2(const char* ATcommand, char* expected_answer1, char* expected_answer2, char* expected_answer3, unsigned int timeout) {

  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;

  memset(response, '\0', 100);    // Initialize the string

  delay(100);

  serialOut.flush();
  serialOut.println(ATcommand);    // Send the AT command
  //  if (strstr(ATcommand, "AT+CIPSEND") != NULL) {
  //    gsmSerial.write(0x1A);
  //  }


  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {
    // if there are data in the UART input buffer, reads it and checks for the asnwer
    if (serialOut.available() != 0) {
      response[x] = serialOut.read();
      x++;
      // check if the desired answer 1  is in the response of the module
      if (strstr(response, expected_answer1) != NULL)
      {
        answer = 1;
        while (serialOut.available()) {
          response[x] = serialOut.read();
          x++;
        }
      }
      // check if the desired answer 2 is in the response of the module
      else if (strstr(response, expected_answer2) != NULL)
      {
        answer = 2;
        while (serialOut.available()) {
          response[x] = serialOut.read();
          x++;
        }
      }
      // check if the desired answer 3 is in the response of the module
      else if (strstr(response, expected_answer3) != NULL)
      {
        answer = 3;
        while (serialOut.available()) {
          response[x] = serialOut.read();
          x++;
        }
      }

    }
  }
  // Waits for the asnwer with time out
  while ((answer == 0) && ((millis() - previous) < timeout));
  //#ifdef dbg
  Serial.println(response);
  //#endif
  return answer;
}


void sendAT(String ATCommand, const char* exptReply, uint32_t timeout, int retry, uint8_t noOflines) {
  int itr = 0;
  //  serialFlush(gsmSerial); /*Flush all the pending inputs in serial buffer*/
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

