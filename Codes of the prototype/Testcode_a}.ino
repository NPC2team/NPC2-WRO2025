#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char* ssid = "CANTV";
const char* password = "Leonardo2607";



AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    // Define the web server route
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "ESP32 Status: " + String(WiFi.status()));
    });

    // Start the web server
    server.begin();
}

void loop() {
    // Nothing needed here for AsyncWebServer
}
