#include <Wire.h>

const int speakerPin = 10;
volatile int freq = 0;

void setup() {
  Wire.begin(8); 
  Wire.onReceive(receiveEvent); 
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  if (freq > 0) {
    tone(speakerPin, freq);
  } else {
    noTone(speakerPin);
  }
  delay(10);
}

void receiveEvent(int bytes) {
  if (bytes >= 2) {
    int highByte = Wire.read();
    int lowByte = Wire.read();
    freq = (highByte << 8) | lowByte;
  }
}
