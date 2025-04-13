const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int frequencies[] = {300, 400, 500, 600, 700, 800, 900, 1000};
const int segPins[] = {A2, A3, 11, 12, 13, A0, A1};

const byte digits[8] = {
  B0000110, B0111011, B0101111, B1100110,
  B1101101, B1111101, B0000111, B1111111
};

unsigned long lastChange = 0;
int displayIdx = 0;
int pressedBtns[8] = {0};
int btnCount = 0;

void setup() {
  Serial.begin(9600); 

  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
}

void showDigit(int num) {
  byte pattern = (num == 0) ? 0 : digits[num - 1];
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], bitRead(pattern, i));
  }
}

void loop() {
  int sum = 0;
  btnCount = 0;

  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      sum += frequencies[i];
      pressedBtns[btnCount++] = i + 1;
    }
  }

  if (btnCount > 0) {
    Serial.println(sum);

    if (millis() - lastChange >= 500) {
      int num = (btnCount == 1) ? pressedBtns[0] : pressedBtns[displayIdx++];
      displayIdx %= btnCount;
      showDigit(num);
      lastChange = millis();
    }
  } else {
    Serial.println(0);  
    showDigit(0);        
  }

  delay(20);
}
