#include <Arduino.h>
int outputPinArray[] = {32, 33, 25, 26, 27, 14, 12};

void pinsSetup(){
 for (size_t i = 0; i < sizeof(outputPinArray)/sizeof(outputPinArray[0]); i++)
  {
    pinMode(outputPinArray[i], OUTPUT);
  }
  pinMode(23, INPUT);
  pinMode(22, INPUT);
  pinMode(21, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
noTone(26);
}
void togglePin(int x) {
  digitalWrite(x, !digitalRead(x));
}

void turnOnPin(int x) {
  digitalWrite(x, HIGH);
}
void turnOffPin(int x) {
  digitalWrite(x, LOW);
}

void boolToPin(int x, bool y) {
  digitalWrite(x, y ? HIGH : LOW);
}