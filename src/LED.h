#include <Arduino.h>
void shiftBlink()
{
  togglePin(32);
  delay(200);
  togglePin(33);
  delay(200);
  togglePin(25);
  togglePin(26);
  delay(500);
  // for (size_t i = 0; i < 3; i++)
  // {
  //   togglePin(outputPinArray[i]);
  // }
  togglePin(32);
  togglePin(33);
  togglePin(25);
  togglePin(26);
}