#include <Arduino.h>
const int btnPin[] = {23, 22, 21, 19};
volatile bool btnPress[4] = {false, false, false, false};
volatile bool lightState = false;
volatile bool readState = false;
volatile bool appendState = false;
volatile bool writeState = false;
void IRAM_ATTR buttonISR0()
{
  btnPress[0] = true;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 0 Pressed");
  writeState = !writeState;
  btnPress[0] = false;
}
void IRAM_ATTR buttonISR1()
{
  btnPress[1] = true;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 1 Pressed");
  appendState = !appendState;
  btnPress[1] = false;
}

void IRAM_ATTR buttonISR2()
{
  btnPress[2] = true;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 2 Pressed");

  readState = !readState;
  btnPress[2] = false;
}

void IRAM_ATTR buttonISR3()
{
  btnPress[3] = true;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn 3 Pressed");

  lightState = !lightState;
  btnPress[3] = false;
}

void buttonSetup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(btnPin[i], INPUT_PULLUP);
  }
  attachInterrupt(digitalPinToInterrupt(btnPin[0]), buttonISR0, FALLING);
  attachInterrupt(digitalPinToInterrupt(btnPin[1]), buttonISR1, FALLING);
  attachInterrupt(digitalPinToInterrupt(btnPin[2]), buttonISR2, FALLING);
  attachInterrupt(digitalPinToInterrupt(btnPin[3]), buttonISR3, FALLING);
}