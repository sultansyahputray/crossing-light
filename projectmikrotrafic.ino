#include <Arduino.h>

const int buttonPin = 22;
const int greenLEDPin = 32;
const int yellowLEDPin = 25;
const int redLEDPin = 26;
const int sevenSegmentPins[] = {15, 2, 4, 5, 18, 19, 21}; // (A, B, C, D, E, F, G)
const int buzzerPin = 33;

bool buttonPressed = false;
int countdownValue = 9;

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(sevenSegmentPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);

  // INIT
  digitalWrite(greenLEDPin, HIGH);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(sevenSegmentPins[i], LOW);
  }
  digitalWrite(buzzerPin, LOW);
}

void loop() {

  bool buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;

    
    // Nyalakan LED merah
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
    for (int i = countdownValue; i >= 0; i--) {
      displayCountdown(i);
      delay(1000); 
    }
    
    // Nyalakan LED kuning selama 3 detik
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(buzzerPin, LOW);

    for (int i = 3; i >= 0; i--) {
      displayCountdown(i);
      delay(1000); 
    }
    
    // Matikan LED kuning
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(1000); 

    // Matikan LED merah, nyalakan LED hijau, dan seven segment mati
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    for (int i = 0; i < 7; i++) {
      digitalWrite(sevenSegmentPins[i], LOW);
    }
  }
  
  if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;
  }
}

void displayCountdown(int number) {
  byte digits[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}  // 9
  };

  for (int i = 0; i < 7; i++) {
    digitalWrite(sevenSegmentPins[i], digits[number][i]);
  }
}