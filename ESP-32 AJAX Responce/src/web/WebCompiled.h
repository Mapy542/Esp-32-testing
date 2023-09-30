#include <ESPAsyncWebServer.h>

 String light;
String gin16;
String gin17;
String gin5;
String gin18;
String gin19;
String gin21;
String gin3;
String gin1;
String gin22;
String gin23;
String gin33;
String gin32;
String gin35;
String gin34;
String gin39;
String gin36;
 String LEDEnable;
void AddServerPages(AsyncWebServer &server){
server.onNotFound([](AsyncWebServerRequest *request){ 
   request->send(404, "text/html", "<html><head><title>you done messed up b-lak-ae</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}button{background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;border: 2px solid #2200aa;border-radius: 5px;}</style></head><body><h1>404...</h1><p> No content here</p><p> Go back <a href = \"/\">home. </a></p><a href=\"/\"><button>Click me</button></a></html>");
});

server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
  LEDEnable = request->arg("LEDEnable");
 String on;
 if (LEDEnable.equals("on")){
   on = "checked";
 }else{
   on = "";
 }
 String off;
 if (LEDEnable.equals("off")){
   off = "checked";
 }else{
   off = "";
 }

request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}</style></head><body><h1>ESP - 32</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#000000\"><p>Go to <a href = \"/light\">light update.</a></p><p> Try on a better <a href=\"https://kentstatesucks.gozips.com\"> domain</a> for size.</p><p> Goto ajax io page <a href=\"/IOView\"> here. </a> </p><hr color=\"#000000\"><form><!--SHOW CURRENT--><p> The light is currently:</p><input type=\"radio\" name=\"LEDEnable\" value=\"on\" " + on + "><label for=\"on\">On</label><br><input  type=\"radio\" name=\"LEDEnable\" value=\"off\" " + off + "><label for=\"off\">Off</label><br></form></body></html>");
});

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ 
 String on;
 if (LEDEnable.equals("on")){
   on = "checked";
 }else{
   on = "";
 }
 String off;
 if (LEDEnable.equals("off")){
   off = "checked";
 }else{
   off = "";
 }

   request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}</style></head><body><h1>ESP - 32</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#000000\"><p>Go to <a href = \"/light\">light update.</a></p><p> Try on a better <a href=\"https://kentstatesucks.gozips.com\"> domain</a> for size.</p><p> Goto ajax io page <a href=\"/IOView\"> here. </a> </p><hr color=\"#000000\"><form><!--SHOW CURRENT--><p> The light is currently:</p><input type=\"radio\" name=\"LEDEnable\" value=\"on\" " + on + "><label for=\"on\">On</label><br><input  type=\"radio\" name=\"LEDEnable\" value=\"off\" " + off + "><label for=\"off\">Off</label><br></form></body></html>");
});

server.on("/IOView", HTTP_GET, [](AsyncWebServerRequest *request){ 

   request->send(200, "text/html", "<html><head><title>ESP32 IO View</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;} .ButtonStyle{background-color: #4e39c9;border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;font-size: 16px;border: #ffffff 2px solid; border-radius: 20px;}table, td {border : 1px solid #4e39c9;border-collapse: collapse;font : 1em Courier;text-align: center;width : 30%;margin-left: 35%}</style></head><body><h1>ESP32 Update Test</h1><p>A University of Akron Money Drain</p><hr color=\"#000000\"><h3> Analog Inputs (ADC1 Only)</h3><table><tr><th>Pin</th><th>Value</th></tr><tr><td>36</td><td><span id=\"gin36\">N.A.</span></td></tr><tr><td>39</td><td><span id=\"gin39\">N.A.</span></td></tr><tr><td>34</td><td><span id=\"gin34\">N.A.</span></td></tr><tr><td>35</td><td><span id=\"gin35\">N.A.</span></td></tr><tr><td>32</td><td><span id=\"gin32\">N.A.</span></td></tr><tr><td>33</td><td><span id=\"gin33\">N.A.</span></td></tr></table><h3> Digital Inputs</h3><table><tr><th>Pin</th><th>Value</th></tr><tr><td>23</td><td><span id=\"gin23\">N.A.</span></td></tr><tr><td>22</td><td><span id=\"gin22\">N.A.</span></td></tr><tr><td>1</td><td><span id=\"gin1\">N.A.</span></td></tr><tr><td>3</td><td><span id=\"gin3\">N.A.</span></td></tr><tr><td>21</td><td><span id=\"gin21\">N.A.</span></td></tr><tr><td>19</td><td><span id=\"gin19\">N.A.</span></td></tr><tr><td>18</td><td><span id=\"gin18\">N.A.</span></td></tr><tr><td>5</td><td><span id=\"gin5\">N.A.</span></td></tr><tr><td>17</td><td><span id=\"gin17\">N.A.</span></td></tr><tr><td>16</td><td><span id=\"gin16\">N.A.</span></td></tr></table><br><p> More ADC pins exist, but ADC2 is utilized entirely by wifi.</p><hr color=\"#000000\"><p> Return <a href=\"/\">Home</a></p><script>setInterval(function() {getInput36();getInput39();getInput34();getInput35();getInput32();getInput33();getInput23();getInput22();getInput1();getInput3();getInput21();getInput19();getInput18();getInput5();getInput17();getInput16();}, 1000);function getInput36() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { document.getElementById(\"gin36\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin36\", true);X_HTTP.send(); }function getInput39() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { document.getElementById(\"gin39\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin39\", true);X_HTTP.send(); }function getInput34() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { document.getElementById(\"gin34\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin34\", true);X_HTTP.send(); }function getInput35() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { document.getElementById(\"gin35\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin35\", true);X_HTTP.send(); }function getInput32() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { document.getElementById(\"gin32\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin32\", true);X_HTTP.send(); }function getInput33() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { document.getElementById(\"gin33\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin33\", true);X_HTTP.send(); }function getInput23() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { document.getElementById(\"gin23\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin23\", true);X_HTTP.send(); }function getInput22() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin22\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin22\", true);X_HTTP.send(); }function getInput1() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin1\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin1\", true);X_HTTP.send(); }function getInput3() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin3\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin3\", true);X_HTTP.send(); }function getInput21() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin21\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin21\", true);X_HTTP.send(); }function getInput19() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin19\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin19\", true);X_HTTP.send(); }function getInput18() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin18\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin18\", true);X_HTTP.send(); }function getInput5() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin5\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin5\", true);X_HTTP.send(); }function getInput17() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin17\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin17\", true);X_HTTP.send(); }function getInput16() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"gin16\").innerHTML = this.responseText;}};X_HTTP.open(\"GET\", \"gin16\", true);X_HTTP.send(); }</script></body></html>");
});

server.on("/gin36", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin36);
});

server.on("/gin39", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin39);
});

server.on("/gin34", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin34);
});

server.on("/gin35", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin35);
});

server.on("/gin32", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin32);
});

server.on("/gin33", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin33);
});

server.on("/gin23", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin23);
});

server.on("/gin22", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin22);
});

server.on("/gin1", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin1);
});

server.on("/gin3", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin3);
});

server.on("/gin21", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin21);
});

server.on("/gin19", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin19);
});

server.on("/gin18", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin18);
});

server.on("/gin5", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin5);
});

server.on("/gin17", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin17);
});

server.on("/gin16", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin16);
});

server.on("/light", HTTP_POST, [](AsyncWebServerRequest *request) {
  light = request->arg("light");
  LEDEnable = request->arg("LEDEnable");
 String on;
 if (LEDEnable.equals("on")){
   on = "checked";
 }else{
   on = "";
 }
 String off;
 if (LEDEnable.equals("off")){
   off = "checked";
 }else{
   off = "";
 }

request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;} </style></head><body><h1>Blink, the Web-form</h1><p>A University of Akron Money Drain</p><hr color=\"#000000\"><form method=\"post\" action=\"/light\" enctype=\'multipart/form-data\'><p> Blinky </p><!--SHOW CURRENT--><input type=\"text\" name=\"light\"  value=" + light + "> Brightness 0-255 <br><p>Enable/Disable</p><input  type=\"radio\" name=\"LEDEnable\" value=\"on\" " + on + "><label for=\"on\">On</label><br><input  type=\"radio\" name=\"LEDEnable\" value=\"off\" " + off + "><label for=\"off\">Off</label><br><br><input  type=\"submit\" value=\"Submit\"></form></body></html>");
});

server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request){ 
 String on;
 if (LEDEnable.equals("on")){
   on = "checked";
 }else{
   on = "";
 }
 String off;
 if (LEDEnable.equals("off")){
   off = "checked";
 }else{
   off = "";
 }

   request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;} </style></head><body><h1>Blink, the Web-form</h1><p>A University of Akron Money Drain</p><hr color=\"#000000\"><form method=\"post\" action=\"/light\" enctype=\'multipart/form-data\'><p> Blinky </p><!--SHOW CURRENT--><input type=\"text\" name=\"light\"  value=" + light + "> Brightness 0-255 <br><p>Enable/Disable</p><input  type=\"radio\" name=\"LEDEnable\" value=\"on\" " + on + "><label for=\"on\">On</label><br><input  type=\"radio\" name=\"LEDEnable\" value=\"off\" " + off + "><label for=\"off\">Off</label><br><br><input  type=\"submit\" value=\"Submit\"></form></body></html>");
});

server.on("/page", HTTP_GET, [](AsyncWebServerRequest *request){ 

   request->send(200, "text/html", "<html><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\"><title>Wifi Test</title><style>body {background-color: #000000;color: #00ff00;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}</style></head><body><h1>UA Robotics</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#00ff00\"><p> <a href=\"/hello\"> Goto hard coded page.</a></p><p><a href=\"http://kentstatesucks.gozips.com\">Try a new domain on</a></p></body></html>");
});

}
