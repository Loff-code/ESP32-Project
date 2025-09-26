#include "secrets.h"
#include <HTTPClient.h>
int frq = 500;
const char *apiSensors = "http://ssh.loffy.dk/api/sensors";
const char *apiState = "http://ssh.loffy.dk/api/devices/state";
const char *apiFreq = "http://ssh.loffy.dk/api/devices/frq";

void sendData(float sensorValue, float humidityValue, float temperatureValue, bool coolState)
{
  HTTPClient http;

  http.begin(apiSensors);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.addHeader("Authorization", "Bearer " ESP_SECRET);
  String postData;
  postData.reserve(100);
  postData += "sensor_data=";
  postData += String(sensorValue);

  postData += "&coolState=";
  postData += String(coolState ? "true" : "false");

  postData += "&time_stamp=";
  if (hour < 10)
    postData += "0";
  postData += String(hour) + ":";
  if (minute < 10)
    postData += "0";
  postData += String(minute) + ":";
  if (second < 10)
    postData += "0";
  postData += String(second);

  postData += "&date_stamp=";
  if (day < 10)
    postData += "0";
  postData += String(day) + "/";
  if (month < 10)
    postData += "0";
  postData += String(month) + "/";
  postData += String(year);

  postData += "&humidity=";
  postData += String(humidityValue);
  postData += "&temperature=";
  postData += String(temperatureValue);

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0)
  {
    String response = http.getString();
    // Serial.println("HTTP Response code: " + String(httpResponseCode));
    if (httpResponseCode != 200)
    {
      Serial.println("Error: " + String(httpResponseCode));
      return;
    }
    // Serial.println("Response: " + response);
    // Serial.print("+");
  }
  else
  {
    Serial.println("Error sending POST request");
  }

  http.end();
}
void getFreq()
{
  HTTPClient http;
  http.begin(apiFreq);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0)
  {
    String response = http.getString();
    // Serial.println("Response: " + response);
    if (httpResponseCode != 200)
    {
      Serial.println("Error: " + String(httpResponseCode));
      return;
    }
    frq = response.toInt();
  }
  else
  {
    Serial.println("Error sending GET request");
  }
  http.end();
}
void getState()
{
  HTTPClient http;
  http.begin(apiState);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0)
  {
    String response = http.getString();
    // Serial.println("Response: " + response);
    // Serial.print(".");
    if (httpResponseCode != 200)
    {
      Serial.println("Error: " + String(httpResponseCode));
      return;
    }
    boolToPin(32, String(response.charAt(1)) == "1");
    boolToPin(33, String(response.charAt(2)) == "1");
    boolToPin(27, String(response.charAt(2)) == "1");
    boolToPin(4, String(response.charAt(2)) == "1");
    boolToPin(25, String(response.charAt(3)) == "1");

    if (String(response.charAt(3)) == "1")
    {
      getFreq();
    }
    String(response.charAt(3)) == "1" ? tone(26, frq) : noTone(26);
  }

  else
  {
    Serial.println("Error sending GET request");
  }
  http.end();
}
// curl -X POST https://loffy.dk/data_receiver      -d "sensor_data=2500.6"      -d "coolState=false"       -d "time_stamp=19:19:19"     -d "date_stamp=19/09/2021"
// curl -X POST 192.168.1.131:4000/data_receiver      -d "sensor_data=2500.6"      -d "coolState=false"       -d "time_stamp=19:19:19"     -d "date_stamp=19/09/2021"
// curl -X POST 192.168.1.131:4000/data_receiver      -d "sensor_data=2500.6"      -d "coolState=true"       -d "time_stamp=19:19:19"     -d "date_stamp=19/09/2021"
// curl -X POST localhost:4000/data_receiver      -d "sensor_data=2500.6"      -d "coolState=true"       -d "time_stamp=19:19:19"     -d "date_stamp=19/09/2021"

// curl -X GET 192.168.1.131:4000/data
// curl -X GET 192.168.1.131:4000/state
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=1"      -d "yellow=1"       -d "green=1"
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=0"      -d "yellow=0"       -d "green=0"
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=0"      -d "yellow=0"       -d "green=1"
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=0"      -d "yellow=1"       -d "green=0"
// curl -X POST 192.168.1.131/light_receiver      -d "red=1"      -d "yellow=0"       -d "green=0"
// curl -X POST https://loffy.dk/light_receiver      -d "red=1"      -d "yellow=0"       -d "green=0"
// curl -X POST http://82.211.219.245/light_receiver     -d "red=1"      -d "yellow=0"       -d "green=0"

// curl -X POST 192.168.1.131:4000/frq_receiver      -d "frq=200"