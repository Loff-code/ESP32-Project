#include <includes.h>
#include "DHT.h"
int Led = 22;       // define LED Interface
int buttonpin = 21; // define D0 Sensor Interface
int val = 0;        // define numeric variables val
// Define the DHT sensor type and the GPIO pin
#define DHTPIN 23     // GPIO pin where the DHT data pin is connected
#define DHTTYPE DHT11 // DHT11 sensor, change to DHT22 if you are using that
DHT dht(DHTPIN, DHTTYPE);

void loopTest()
{
  val = digitalRead(buttonpin); // digital interface will be assigned a value of pin 3 to read val
  if (val == HIGH)              // When the sound detection module detects a signal, LED flashes
  {
    digitalWrite(Led, HIGH);
  }
  else
  {
    digitalWrite(Led, LOW);
  }
  Serial.print(val);
  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius by default

  // Check if the readings failed
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print the results to Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));
}

void setupTest()
{
  pinMode(Led, OUTPUT);      // define LED as output interface
  pinMode(buttonpin, INPUT); // output interface D0 is defined sensor
  Serial.println(F("DHT Sensor example with ESP32"));
  dht.begin();

  pinMode(trans_pin, OUTPUT); // transmit is ouput
  pinMode(recv_pin, INPUT);   // receive is input
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

    break;

  case ACTION:
    lightLVL = light1();
    sendData(lightLVL, true);
    loopTest();
    getDistance();
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
