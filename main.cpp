#include <includes.h>
void loopTest(){
}
void setupTest(){
}

void setup() {
  Serial.begin(921600);
  Serial.println("Hello World!");
  wifiSetup();
  pinsSetup();
  spiffSetup();
  setupTest();
  buttonSetup();
}


void loop() {
    getWifi();
    delay(100);
    shiftBlink();
    delay(100);
    int lightLVL = light(lightState, appendState);
    sendData(lightLVL);
    delay(100);
    readState = fileRead(readState);
    // uploadFileToServer("/dir/test.txt");
    loopTest();
    delay(1000);
    appendState, writeState = fileWrite("Hello World!", writeState);
}
