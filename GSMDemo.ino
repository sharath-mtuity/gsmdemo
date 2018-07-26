


#define pin_LED 13
void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(9600);
  pinMode(pin_LED,OUTPUT);
  Serial.write("In start");

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_LED,HIGH);
    Serial.write("High");

  delay(250);
  digitalWrite(pin_LED,LOW);
      Serial.write("low");

  delay(250);
}
