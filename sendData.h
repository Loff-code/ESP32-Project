#include <HTTPClient.h>

const char *serverAddress = "http://192.168.1.131:4000/data_receiver";
const char *serverAddress1 = "http://192.168.1.131:4000/state";

void sendData(float sensorValue, bool coolState) {
  HTTPClient http;

  http.begin(serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData;
  postData.reserve(100); // Reserve memory for the string to avoid frequent reallocations

  postData += "sensor_data=";
  postData += String(sensorValue);

  postData += "&coolState=";
  postData += String(coolState ? "true" : "false");

  postData += "&time_stamp=";
  if (hour < 10) postData += "0";
  postData += String(hour) + ":";
  if (minute < 10) postData += "0";
  postData += String(minute) + ":";
  if (second < 10) postData += "0";
  postData += String(second);

  postData += "&date_stamp=";
  if (day < 10) postData += "0";
  postData += String(day) + "/";
  if (month < 10) postData += "0";
  postData += String(month) + "/";
  postData += String(year);

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    // Serial.println("HTTP Response code: " + String(httpResponseCode));
    if (httpResponseCode != 200) {
      Serial.println("Error: " + String(httpResponseCode));
      return;
    }
    // Serial.println("Response: " + response);
     Serial.print("+");
  } else {
    Serial.println("Error sending POST request");
  }

  http.end();
}

void getState() {
  HTTPClient http;
  http.begin(serverAddress1);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    String response = http.getString();
    // Serial.println("Response: " + response);
    Serial.print(".");
    if (httpResponseCode != 200) {
      Serial.println("Error: " + String(httpResponseCode));
      return;
    }
    boolToPin(32, String(response.charAt(1)) == "1");
    boolToPin(33, String(response.charAt(2)) == "1");
    boolToPin(25, String(response.charAt(3)) == "1");
    String(response.charAt(3)) == "1" ? tone(26, 1000) : noTone(26);
    } else {
    Serial.println("Error sending GET request");
  }
  http.end();
}

// curl -X POST 192.168.1.131:4000/data_receiver      -d "sensor_data=2500.6"      -d "coolState=false"       -d "time_stamp=19:19:19"     -d "date_stamp=19/09/2021"
// curl -X POST 192.168.1.131:4000/data_receiver      -d "sensor_data=2500.6"      -d "coolState=true"       -d "time_stamp=19:19:19"     -d "date_stamp=19/09/2021"
// curl -X GET 192.168.1.131:4000/data
// curl -X GET 192.168.1.131:4000/state
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=1"      -d "yellow=1"       -d "green=1"
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=0"      -d "yellow=0"       -d "green=0"
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=0"      -d "yellow=0"       -d "green=1"
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=0"      -d "yellow=1"       -d "green=0"
// curl -X POST 192.168.1.131:4000/light_receiver      -d "red=1"      -d "yellow=0"       -d "green=0"