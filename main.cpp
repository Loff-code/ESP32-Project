#include <includes.h>

void loopTest()
{
}

void setupTest()
{
}

void setup()
{
  Serial.begin(921600);
  Serial.println("Hello World!");
  wifiSetup();
  pinsSetup();
  // spiffSetup();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  buttonSetup();
  setupTest();
  playSong();
  
}

void loop()
{
  switch (stateReg)
  {
  case IDLE:
    getWifi();
    getState();
    updateDateTime();
    check(everyX(5));
    loopTest();
    break;

  case ACTION:
    lightLVL = light1();
    sendData(lightLVL, appendState);
    stateReg = IDLE;
    break;

  default:
    break;
  }
}

// readState = fileRead(readState);
//  uploadFileToServer("/dir/test.txt");

// appendState, writeState = fileWrite("Hello World!", writeState);
//  printLocalTime();
//  if (actionState) {
//    // Serial.println("Action");
//    // readState = !readState;
//    // delay(100);
//    // shiftBlink();
//    // delay(100);
//    // lightLVL = light(lightState, appendState);
//    lightLVL = light1();
//    sendData(lightLVL, appendState);
//    actionState = false;
//  }
