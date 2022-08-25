// Import required libraries
#include "deneyap.h"
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

// Replace with your network credentials
//WiFi SSID: DEVRIALEM
//WiFi
//WiFi Password: 12345 -> your home
// I use AccessPoint(AP) for now.
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
const char* ssid = "DEVRIALEM";
const char* passwd = "12345678";

void notFound(AsyncWebServerRequest *request) {
  request->send(404,"text/plain", "Page Not Found.");
}
void setup() {  
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, passwd);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }


  // Print Deneyap_Kart Local IP Address
  Serial.println("");
  Serial.print("Ip Address: ");
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  // Start server with define 404 page
  server.onNotFound(notFount);
  server.begin();
}


void loop() {
  // it's blank, i dont get sensor. for now i tkink.
}
/* To send a text data a server url
  server.on("/controlBuildingStatus", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", controlBuildingStatus().c_str());
  });
   To send a text file
  server.on("/olcumler.txt", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/olcumler.txt", String(), true);
  });
   To send a javascript file to server 
  server.on("/leaflet.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/leaflet.js", "text/javascript");
  });
*/
