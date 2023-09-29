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

  server.begin();

  pinMode(2, OUTPUT);
}

void loop() {
  dnsServer.processNextRequest();
  Serial.println(light + ", " + LEDEnable);
  if (LEDEnable.equals("on")) {
    analogWrite(2, light.toInt());
  } else {
    analogWrite(2, 0);
  }
}