#include <SPIFFS.h>
#include <SDtest.h>

#define FORMAT_SPIFFS_IF_FAILED true

void spiffSetup(){

  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  if (SPIFFS.mkdir("/dir")) {
    Serial.println("Directory created");
  } else {
    Serial.println("Directory exists");
  }
  listDir(SPIFFS, "/",0);

}



bool fileWrite(String x, bool state){
  if (state)
  {
  File file = SPIFFS.open("/dir/test.txt", "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return false;
  }

  Serial.println("Writing to file");
  file.println("x");
  file.close();

  return true, false;
}else{
  return false, false;
}
}
bool fileRead(bool state){
  if (state)
  {
  File file = SPIFFS.open("/dir/test.txt", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return false;
  }

  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  }
  return false;
}


void fileAppend(String x, bool state){
  if (state)
  {
  File file = SPIFFS.open("/dir/test.txt", "a");
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }

  Serial.print(".");
  file.println(x);
  file.close();
  }
}

void uploadFileToServer(String filePath) {
  const char* serverAddress = "http://192.168.1.131/upload.php"; // Replace with your server address

  // Create HTTPClient object
  HTTPClient http;

  // Open the file
  File file = SPIFFS.open(filePath, FILE_READ);

  // Check if the file opened successfully
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // Get file size
  size_t fileSize = file.size();

  // Allocate a buffer to store the file contents
  uint8_t *buffer = (uint8_t *)malloc(fileSize);

  // Read file into buffer
  file.read(buffer, fileSize);

  // Close the file
  file.close();

  // Create a new HTTPClient object
  WiFiClient client;
  if (!http.begin(client, serverAddress)) {
    Serial.println("Failed to connect to server");
    free(buffer);
    return;
  }

  // Prepare the request payload
  String boundary = "---------------------------" + String(random(0xffffff), HEX);
  String formData = "";
  formData += "--" + boundary + "\r\n";
  formData += "Content-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\n";
  formData += "Content-Type: text/plain\r\n\r\n";

  // Send the header
  http.addHeader("Content-Type", "multipart/form-data; boundary=" + boundary);
  http.addHeader("Content-Length", String(fileSize + formData.length()));
  
  // Start the POST request
  int httpCode = http.POST("");

  // Check for a successful request
  if (httpCode == HTTP_CODE_OK) {
    // Send the file content
    client.write((const uint8_t *)formData.c_str(), formData.length());
    client.write(buffer, fileSize);

    // Send the footer for multipart form data
    String footer = "\r\n--" + boundary + "--\r\n";
    client.write((const uint8_t *)footer.c_str(), footer.length());

    // Get response
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.printf("HTTP request failed with error code %d\n", httpCode);
  }

  // Free buffer memory
  free(buffer);

  // End HTTP connection
  http.end();
}
