//Define button pins, speaker pin, and the frequencies
const int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int speaker = 10;
const int f[] = {300, 400, 500, 600, 700, 800, 900, 1000};

//7-segment display pins [a, b, c, d, e, f, g]
const int segPins[] = {0, 1, 11, 12, 13, A0, A1};

//Patterns for digits 1-8 (common cathode)
const byte digits[8] = {
  B0000110, //1
  B0111011, //2
  B0101111, //3
  B1100110, //4
  B1101101, //5
  B1111101, //6
  B0000111, //7
  B1111111  //8
};

unsigned long lastChange = 0;
int displayIdx = 0;
int pressedBtns[8] = {0};
int btnCount = 0;

void setup() {
  // Set buttons as inputs with pull-up resistors
  for (int i = 0; i < 8; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  
  // Set speaker as output
  pinMode(speaker, OUTPUT);
  
  // Set segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
}

void showDigit(int num) {
  if (num == 0) { // Close all segments as default
    for (int i = 0; i < 7; i++) {
      digitalWrite(segPins[i], LOW);
    }
  } else {
    byte pattern = digits[num - 1];
    for (int i = 0; i < 7; i++) {
      digitalWrite(segPins[i], bitRead(pattern, i));
    }
  }
}

void loop() {
  int sum = 0;
  btnCount = 0; // Reset button count each loop

  // Check each button
  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttons[i]) == LOW) { // Check for active-low button press
      sum += f[i];
      pressedBtns[btnCount] = i + 1; // Store button number (1-8)
      btnCount++;
    }
  }
  
  if (btnCount > 0) {
    tone(speaker, sum);
    
    if (millis() - lastChange >= 500) { // Alternate digits every 500ms
      if (btnCount == 1) {
        showDigit(pressedBtns[0]);
      } else {
        showDigit(pressedBtns[displayIdx]);
        displayIdx = (displayIdx + 1) % btnCount;
      }
      lastChange = millis();
    }
  } else {
    noTone(speaker);
    showDigit(0); // Show nothing (clear the display) when no button is pressed
  }
  
  delay(20); // Short delay for debouncing
}
