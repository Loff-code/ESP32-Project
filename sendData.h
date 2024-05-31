#include <HTTPClient.h>

const char *serverAddress = "http://192.168.1.131/data_receiver.php";

void sendData(float sensorValue) {
  HTTPClient http;

  http.begin(serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String postData = "sensor_data=" + String(sensorValue);

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    // Serial.println("HTTP Response code: " + String(httpResponseCode));
    // Serial.println("Response: " + response);
  } else {
    // Serial.println("Error sending POST request");
  }

  http.end();
}
