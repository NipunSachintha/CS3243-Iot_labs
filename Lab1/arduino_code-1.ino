// Name: GUNARATHNA DMNS
// Index Number: 220185P

const int buttonPins[8] = {2,3,4,5,6,7,8,9}; // Push button pins
const int frequencies[8] = {300, 400, 500, 600, 700, 800, 900, 1000}; // Assigned frequencies
const int buzzerPin  = 10; // Speaker output pin

void setup() {
    Serial.begin(9600); // Initialize Serial Monitor
    for (int i = 0; i < 8; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP); // Set buttons as input with internal pull-up
      
    }
}

void loop() {
    int totalFreq = 0;
    bool keyPressed = false;

    
    for (int i = 0; i < 8; i++) {
        if (digitalRead(buttonPins[i]) == LOW) 
        { 
            totalFreq += frequencies[i];
            keyPressed = true;
            
        }
    }

    if (keyPressed) {
        
        tone(buzzerPin , totalFreq); 
    } else {
        noTone(buzzerPin );
    }

    delay(20); 
}