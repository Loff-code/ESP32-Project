#include <Arduino.h>
const int btnPin[] = {23, 22, 21, 19}; // Pins where your buttons are connected
volatile bool btnPress[4] = {false, false, false, false}; // Flags to indicate button press
volatile bool lightState = false; // Flag to indicate light state
volatile bool readState = false; // Flag to indicate light state
volatile bool appendState = false; // Flag to indicate light state
volatile bool writeState = false; // Flag to indicate light state
void IRAM_ATTR buttonISR0() {
  btnPress[0] = true; // Set flag to true indicating button press
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 0 Pressed");
  writeState = !writeState;
  btnPress[0] = false;
}
void IRAM_ATTR buttonISR1() {
  btnPress[1] = true; // Set flag to true indicating button press
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 1 Pressed");
  appendState = !appendState;
  btnPress[1] = false;
}

void IRAM_ATTR buttonISR2() {
  btnPress[2] = true; // Set flag to true indicating button press
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 2 Pressed");
  
  readState = !readState;
  btnPress[2] = false;
}

void IRAM_ATTR buttonISR3() {
  btnPress[3] = true; // Set flag to true indicating button press
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 3 Pressed");
  
  lightState = !lightState;
  btnPress[3] = false;
}

void buttonSetup() {
  for (int i = 0; i < 4; i++) {
    pinMode(btnPin[i], INPUT_PULLUP); // Set button pin as input with pull-up
  }
  attachInterrupt(digitalPinToInterrupt(btnPin[0]), buttonISR0, FALLING); // Attach interrupt to button pin
  attachInterrupt(digitalPinToInterrupt(btnPin[1]), buttonISR1, FALLING); // Attach interrupt to button pin
  attachInterrupt(digitalPinToInterrupt(btnPin[2]), buttonISR2, FALLING); // Attach interrupt to button pin
  attachInterrupt(digitalPinToInterrupt(btnPin[3]), buttonISR3, FALLING); // Attach interrupt to button pin
}