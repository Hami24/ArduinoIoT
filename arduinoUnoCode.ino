#include "SoftwareSerial.h"
SoftwareSerial esp(2, 3);

void setup() {
  pinMode(9,OUTPUT);
  esp.begin(9600);
  Serial.begin(9600);
}

void loop (){
  if (esp.available()) {
    char request = esp.read();
    Serial.println("Received character:")
    Serial.println(request);
    switch (request) {
      case '1':
          digitalWrite(9,HIGH);
        break;
      case '0':
          digitalWrite(9,LOW);
        break;
    } 
  }
}
