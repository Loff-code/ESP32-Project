#include <includes.h>



bool everyX(int x){
  bool a = iv(0, 3);
  for (size_t i = 1; i < 60/x; i++)
  {
    a = a || iv(x*i-1, x*i+1);
  }
return a;
  
}

void loopTest() {
  // check(iv(0, 5), iv(10, 15), iv(20, 25), iv(30, 35), iv(40, 45), iv(50, 55));
  check(everyX(5));
}

void setupTest() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

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
    readState = fileRead(readState);
    // uploadFileToServer("/dir/test.txt");
    updateDateTime();
    loopTest();
    appendState, writeState = fileWrite("Hello World!", writeState);
    // printLocalTime();
    if (actionState) {
      Serial.println("Action");
      // readState = !readState;
      delay(100);
      shiftBlink();
      delay(100);
      lightLVL = light(lightState, appendState);
      sendData(lightLVL, appendState);
      actionState = false;
    }
}

