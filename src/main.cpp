#include <includes.h>
#include <getDHT.h>
#include <WiFiClientSecure.h>
#include <Update.h>

#define CURRENT_VERSION "1.1.0"
const char *version_url = "https://loffy.dk/api/ota/esp32/version";
const char *firmware_url = "https://loffy.dk/api/ota/esp32/firmware";

void otaUpdate()
{
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient https;
  if (https.begin(client, version_url))
  {
    if (https.GET() == 200)
    {
      String newVersion = https.getString();
      newVersion.trim();
      if (newVersion != CURRENT_VERSION)
      {
        https.end();
        if (https.begin(client, firmware_url))
        {
          if (https.GET() == 200)
          {
            int len = https.getSize();
            WiFiClient *stream = https.getStreamPtr();
            if (Update.begin(len))
            {
              Update.writeStream(*stream);
              if (Update.end() && Update.isFinished())
                ESP.restart();
            }
          }
          https.end();
        }
      }
    }
    https.end();
  }
}

void loopTest()
{
  otaUpdate();
}

void setupTest() {}

void setup()
{
  Serial.begin(921600);
  Serial.println("Hello World!");
  wifiSetup();
  pinsSetup();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  setupTest();
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
    stateReg = IDLE;
    break;
  default:
    break;
  }
}
