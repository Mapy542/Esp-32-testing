#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include <DNSServer.h>

#include "web\WebCompiled.h"

const char *ssid = "ESP-AP";
const char *password = "password";

AsyncWebServer server(80);
DNSServer dnsServer;

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  dnsServer.start(
      53, "*",
      WiFi.softAPIP()); // define all domains to point to WiFi.softAPIP()

  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  AddServerPages(server); // run python complied web include script
  Serial.println("Server pages initialized");

  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "This works as well");
  });

  server.begin();
}

void loop() { dnsServer.processNextRequest(); }