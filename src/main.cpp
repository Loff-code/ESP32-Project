#include <includes.h>
#include <getDHT.h>

void loopTest()
{
}

void setupTest()
{
  // Setup distance
  // pinMode(trans_pin, OUTPUT);
  // pinMode(recv_pin, INPUT);
}

void setup()
{
  Serial.begin(921600);
  Serial.println("Hello World!");
  wifiSetup();
  pinsSetup();
  // spiffSetup();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // buttonSetup();
  setupTest();
  // playSong();
  tone(26, frq);
  noTone(26);

  dht.begin();
}

void loop()
{
  switch (stateReg)
  {
  case IDLE:
    getWifi();
    getState();
    updateDateTime();
    check(second % 5 == 0);

    break;

  case ACTION:
    lightLVL = light1();
    sendData(lightLVL, dht.readHumidity(), dht.readTemperature(), digitalRead(12));
    loopTest();
    // getDistance();

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
