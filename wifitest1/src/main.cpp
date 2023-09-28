#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include <DNSServer.h>

std::string page =
#include "page.html"
    ;

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

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello World");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", page.c_str());
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(
        404, "text/html",
        "<html><head><title>404</title></head><body><h1>404</h1><p>Not "
        "found</p> <p> Return <a href=\"/\">home.</a></p></body></html>");
  });

  server.begin();
}

void loop() { dnsServer.processNextRequest(); }