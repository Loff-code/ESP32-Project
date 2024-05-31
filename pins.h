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

}
void togglePin(int x) {
  digitalWrite(x, !digitalRead(x));
}
