#include <WiFi.h>
#include <secrets.h>
#include <HTTPClient.h>
#include "time.h"
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
bool isWiFiConnecte = false;

void wifiSetup()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void get_network_info()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("[*] Network information for ");
    Serial.println(WIFI_SSID);
    Serial.println("[+] BSSID : " + WiFi.BSSIDstr());
    Serial.print("[+] Gateway IP : ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("[+] Subnet Mask : ");
    Serial.println(WiFi.subnetMask());
    Serial.println((String) "[+] RSSI : " + WiFi.RSSI() + " dB");
    Serial.print("[+] ESP32 IP : ");
    Serial.println(WiFi.localIP());
  }
}

void getWifi()
{
  if (WiFi.status() == WL_CONNECTED && !isWiFiConnecte)
  {
    Serial.println("Connected to WiFi");
    digitalWrite(LED_BUILTIN, HIGH);
    isWiFiConnecte = true;
    get_network_info();
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(200);
    isWiFiConnecte = false;
  }
}

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
