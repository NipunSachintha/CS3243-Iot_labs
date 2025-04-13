#include <Wire.h>

const int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int f[] = {300, 400, 500, 600, 700, 800, 900, 1000};
const int segPins[] = {A2, A3, 11, 12, 13, A0, A1};
const byte digits[8] = {
  B0000110, B0111011, B0101111, B1100110,
  B1101101, B1111101, B0000111, B1111111
};

const int diagLED = 10;
unsigned long lastChange = 0;
unsigned long lastHealthSend = 0;
unsigned long lastHealthResponse = 0;
int displayIdx = 0;
int pressedBtns[8] = {0};
int btnCount = 0;

void setup() {
  Wire.begin(); // Master
  for (int i = 0; i < 8; i++) pinMode(buttons[i], INPUT_PULLUP);
  for (int i = 0; i < 7; i++) pinMode(segPins[i], OUTPUT);
  pinMode(diagLED, OUTPUT);
}

void showDigit(int num) {
  byte pattern = (num == 0) ? 0 : digits[num - 1];
  for (int i = 0; i < 7; i++) digitalWrite(segPins[i], bitRead(pattern, i));
}

void loop() {
  int sum = 0;
  btnCount = 0;

  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      sum += f[i];
      pressedBtns[btnCount] = i + 1;
      btnCount++;
    }
  }

  if (btnCount > 0) {
    // Send frequency to Board B
    Wire.beginTransmission(8);
    Wire.write(highByte(sum));
    Wire.write(lowByte(sum));
    Wire.endTransmission();

    if (millis() - lastChange >= 500) {
      showDigit(pressedBtns[(btnCount == 1) ? 0 : displayIdx]);
      displayIdx = (displayIdx + 1) % btnCount;
      lastChange = millis();
    }
  } else {
    showDigit(0);
  }

  // Health check every 1s
  if (millis() - lastHealthSend >= 1000) {
    Wire.requestFrom(8, 1);
    if (Wire.available()) {
      byte response = Wire.read();
      if (response == 1) lastHealthResponse = millis();
    }
    lastHealthSend = millis();
  }

  // Check if board is alive
  digitalWrite(diagLED, (millis() - lastHealthResponse < 2000) ? HIGH : LOW);

  delay(20);
}
