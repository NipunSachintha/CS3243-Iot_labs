#include <Wire.h>

const int speaker = 10;
const int diagLED = 6;
unsigned long lastMsgTime = 0;
int receivedFreq = 0;

void setup() {
  Wire.begin(8);  // Slave address 8
  Wire.onReceive(receiveData);
  Wire.onRequest(sendHealth);
  pinMode(speaker, OUTPUT);
  pinMode(diagLED, OUTPUT);
}

void loop() {
    if (millis() - lastMsgTime < 2000 && receivedFreq > 0) {
    	tone(speaker, receivedFreq, 20);
        digitalWrite(diagLED, HIGH); 
  } else {
    noTone(speaker);           
  }
}

void receiveData(int bytes) {
  if (bytes == 2) {
    int highB = Wire.read(); 
    int lowB = Wire.read();  
    receivedFreq = word(highB, lowB); 
    lastMsgTime = millis();  
  }
}


void sendHealth() {
  Wire.write(1);  
}
