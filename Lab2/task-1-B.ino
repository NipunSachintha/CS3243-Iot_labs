const int speakerPin = 10;
String inStr = "";

void setup() {
  Serial.begin(9600); 
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\n') {
      int freq = inStr.toInt();
      if (freq > 0) {
        tone(speakerPin, freq);
      } else {
        noTone(speakerPin);
      }
      inStr = "";
    } else {
      inStr += ch;
    }
  }
}
