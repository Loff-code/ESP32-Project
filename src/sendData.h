#include <HTTPClient.h>
int frq = 500;
// const char host = "https://loffy.dk"
// const char *serverAddress = "https://loffy.dk/data_receiver";
// const char *serverAddress1 = "https://loffy.dk/state";
// const char *serverAddress2 = "https://loffy.dk/frq";
const char *serverAddress = "http://192.168.68.110/data_receiver";
const char *serverAddress1 = "http://192.168.68.110/state";
const char *serverAddress2 = "http://192.168.68.110/frq";

void sendData(float sensorValue, bool coolState)
{
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
  http.begin(serverAddress2);
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
  http.begin(serverAddress1);
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