#include <Arduino.h>

const int button_pin = 22;
const int green_LED = 32;
const int yellow_LED = 25;
const int red_LED = 26;
const int seven_segment_pins[] = {15, 2, 4, 5, 18, 19, 21}; // (A, B, C, D, E, F, G)
const int buzzer_pin = 33;

bool button_pressed = false;
int countdown_value = 9;

void setup() {

  pinMode(button_pin, INPUT_PULLUP);
  pinMode(green_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(seven_segment_pins[i], OUTPUT);
  }
  pinMode(buzzer_pin, OUTPUT);

  // INIT
  digitalWrite(green_LED, HIGH);
  digitalWrite(yellow_LED, LOW);
  digitalWrite(red_LED, LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(seven_segment_pins[i], LOW);
  }
  digitalWrite(buzzer_pin, LOW);
}

void loop() {

  bool button_state = digitalRead(button_pin);
  
  if (button_state == LOW && !button_pressed) {
    button_pressed = true;

    
    // Nyalakan LED merah
    digitalWrite(green_LED, LOW);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(red_LED, HIGH);
    digitalWrite(buzzer_pin, HIGH);
    
    for (int i = countdown_value; i >= 0; i--) {
      displayCountdown(i);
      delay(1000); 
    }
    
    // Nyalakan LED kuning selama 3 detik
    digitalWrite(green_LED, LOW);
    digitalWrite(yellow_LED, HIGH);
    digitalWrite(red_LED, LOW);
    digitalWrite(buzzer_pin, LOW);

    for (int i = 3; i >= 0; i--) {
      displayCountdown(i);
      delay(1000); 
    }
    
    // Matikan LED kuning
    digitalWrite(green_LED, LOW);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(red_LED, LOW);
    digitalWrite(buzzer_pin, LOW);
    delay(1000); 

    // Matikan LED merah, nyalakan LED hijau, dan seven segment mati
    digitalWrite(green_LED, HIGH);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(red_LED, LOW);
    for (int i = 0; i < 7; i++) {
      digitalWrite(seven_segment_pins[i], LOW);
    }
  }
  
  if (button_state == HIGH && button_pressed) {
    button_pressed = false;
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
    digitalWrite(seven_segment_pins[i], digits[number][i]);
  }
}