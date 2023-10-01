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

  server.on("/live", HTTP_POST, [](AsyncWebServerRequest *request) {
    light = request->arg("light");
    LEDEnable = request->arg("LEDEnable");
    request->send(200, "text/plain", "OK");
  });

  Serial.println("Server pages initialized");

  server.begin();

  pinMode(2, OUTPUT);
  pinMode(36, INPUT);
  pinMode(39, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);
  pinMode(23, INPUT);
  pinMode(22, INPUT);
  pinMode(1, INPUT);
  pinMode(3, INPUT);
  pinMode(21, INPUT);
  pinMode(19, INPUT);
  pinMode(18, INPUT);
  pinMode(5, INPUT);
  pinMode(17, INPUT);
  pinMode(16, INPUT);
}

void loop() {
  dnsServer.processNextRequest();
  if (LEDEnable.equals("on")) {
    analogWrite(2, light.toInt());
  } else {
    analogWrite(2, 0);
  }

  gin36 = String(analogRead(36));
  gin39 = String(analogRead(39));
  gin34 = String(analogRead(34));
  gin35 = String(analogRead(35));
  gin32 = String(analogRead(32));
  gin33 = String(analogRead(33));

  gin23 = String(digitalRead(23));
  gin22 = String(digitalRead(22));
  gin1 = String(digitalRead(1));
  gin3 = String(digitalRead(3));
  gin21 = String(digitalRead(21));
  gin19 = String(digitalRead(19));
  gin18 = String(digitalRead(18));
  gin5 = String(digitalRead(5));
  gin17 = String(digitalRead(17));
  gin16 = String(digitalRead(16));
  delay(100);
}