const int buttonPin = 2;  // Pin for the button
const int relayPin = 3;   // Pin for the relay

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Button as input with internal pull-up
  pinMode(relayPin, OUTPUT);        // Relay as output
  digitalWrite(relayPin, HIGH);     // Relay initially HIGH (off)
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {         // Button is pressed
    while (digitalRead(buttonPin) == LOW) { // Keep toggling while button is held
      digitalWrite(relayPin, LOW);  // Turn relay on (LOW)
      delay(50);                    // Wait for 50 milliseconds
      digitalWrite(relayPin, HIGH); // Turn relay off (HIGH)
      delay(50);                    // Wait for 50 milliseconds
    }
  }
}
