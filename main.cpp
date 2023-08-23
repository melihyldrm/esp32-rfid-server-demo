// #include <Arduino.h>
// #ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "ESP-32 AP";
const char* password = "123456789";

const char* PARAM_INPUT_1 = "input1";

// HTML web page to handle input field input1
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    ad-soyad: <input type="text" name="input1">
    <input type="submit" value="Submit">
  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
      // Configure the ESP in Access Point mode
      WiFi.mode(WIFI_AP);
      WiFi.softAP("ESP-32 AP", "123456789");
      
      Serial.println();
      Serial.print("Access Point IP Address: ");
      Serial.println(WiFi.softAPIP());

    // Send web page with input fields to client
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html);
    });

    // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage;
      String inputParam;
      // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
      if (request->hasParam(PARAM_INPUT_1)) {
        inputMessage = request->getParam(PARAM_INPUT_1)->value();
        inputParam = PARAM_INPUT_1;
      }
      Serial.println(inputMessage);
      request->send(200, "text/html", index_html); 
    });
    server.onNotFound(notFound);
    server.begin();
  }

void loop() {
}