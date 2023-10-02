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

request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}</style></head><body><h1>ESP - 32</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#000000\"><p>Go to <a href = \"/light\">light update.</a></p><p> Try on a better <a href=\"http://kentstatesucks.gozips.com\"> domain</a> for size.</p><p> Goto ajax io page <a href=\"/IOView\"> here. </a> </p><hr color=\"#000000\"><form><!--SHOW CURRENT--><p> The light is currently:</p><input type=\"radio\" name=\"LEDEnable\" value=\"on\" " + on + "><label for=\"on\">On</label><br><input  type=\"radio\" name=\"LEDEnable\" value=\"off\" " + off + "><label for=\"off\">Off</label><br></form></body></html>");
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

   request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}</style></head><body><h1>ESP - 32</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#000000\"><p>Go to <a href = \"/light\">light update.</a></p><p> Try on a better <a href=\"http://kentstatesucks.gozips.com\"> domain</a> for size.</p><p> Goto ajax io page <a href=\"/IOView\"> here. </a> </p><hr color=\"#000000\"><form><!--SHOW CURRENT--><p> The light is currently:</p><input type=\"radio\" name=\"LEDEnable\" value=\"on\" " + on + "><label for=\"on\">On</label><br><input  type=\"radio\" name=\"LEDEnable\" value=\"off\" " + off + "><label for=\"off\">Off</label><br></form></body></html>");
});

server.on("/IOView", HTTP_GET, [](AsyncWebServerRequest *request){ 

   request->send(200, "text/html", "<html><head><title>ESP32 IO View</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;} .ButtonStyle{background-color: #4e39c9;border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;font-size: 16px;border: #ffffff 2px solid; border-radius: 20px;}table, td {border : 1px solid #4e39c9;border-collapse: collapse;font : 1em Courier;text-align: center;width : 30%;margin-left: 35%}</style></head><body><h1>ESP32 IO Viewport</h1><p>A University of Akron Money Drain</p><hr color=\"#000000\"><h3> Analog Inputs (ADC1 Only)</h3><table><tr><th>Pin</th><th>Value</th></tr><tr><td>36</td><td><span id=\"gin36\">N.A.</span></td></tr><tr><td>39</td><td><span id=\"gin39\">N.A.</span></td></tr><tr><td>34</td><td><span id=\"gin34\">N.A.</span></td></tr><tr><td>35</td><td><span id=\"gin35\">N.A.</span></td></tr><tr><td>32</td><td><span id=\"gin32\">N.A.</span></td></tr><tr><td>33</td><td><span id=\"gin33\">N.A.</span></td></tr></table><h3> Digital Inputs</h3><table><tr><th>Pin</th><th>Value</th></tr><tr><td>23</td><td><span id=\"gin23\">N.A.</span></td></tr><tr><td>22</td><td><span id=\"gin22\">N.A.</span></td></tr><tr><td>1</td><td><span id=\"gin1\">N.A.</span></td></tr><tr><td>3</td><td><span id=\"gin3\">N.A.</span></td></tr><tr><td>21</td><td><span id=\"gin21\">N.A.</span></td></tr><tr><td>19</td><td><span id=\"gin19\">N.A.</span></td></tr><tr><td>18</td><td><span id=\"gin18\">N.A.</span></td></tr><tr><td>5</td><td><span id=\"gin5\">N.A.</span></td></tr><tr><td>17</td><td><span id=\"gin17\">N.A.</span></td></tr><tr><td>16</td><td><span id=\"gin16\">N.A.</span></td></tr></table><br><p> More ADC pins exist, but ADC2 is utilized entirely by wifi.</p><hr color=\"#000000\"><p> Return <a href=\"/\">Home</a></p><script>setInterval(function() {getData();}, 250);function getData() {var X_HTTP = new XMLHttpRequest();X_HTTP.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) { var data = this.responseText.split(\",\");document.getElementById(\"gin36\").innerHTML = data[0];document.getElementById(\"gin39\").innerHTML = data[1];document.getElementById(\"gin34\").innerHTML = data[2];document.getElementById(\"gin35\").innerHTML = data[3];document.getElementById(\"gin32\").innerHTML = data[4];document.getElementById(\"gin33\").innerHTML = data[5];document.getElementById(\"gin23\").innerHTML = data[6];document.getElementById(\"gin22\").innerHTML = data[7];document.getElementById(\"gin1\").innerHTML = data[8];document.getElementById(\"gin3\").innerHTML = data[9];document.getElementById(\"gin21\").innerHTML = data[10];document.getElementById(\"gin19\").innerHTML = data[11];document.getElementById(\"gin18\").innerHTML = data[12];document.getElementById(\"gin5\").innerHTML = data[13];document.getElementById(\"gin17\").innerHTML = data[14];document.getElementById(\"gin16\").innerHTML = data[15];}};X_HTTP.open(\"GET\", \"getioview\", true);X_HTTP.send(); }</script></body></html>");
});

server.on("/getioview", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", gin36 + "," + gin39 + "," + gin34 + "," + gin35 + "," + gin32 + "," + gin33 + "," + gin23 + "," + gin22 + "," + gin1 + "," + gin3 + "," + gin21 + "," + gin19 + "," + gin18 + "," + gin5 + "," + gin17 + "," + gin16);
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

server.on("/livesend", HTTP_GET, [](AsyncWebServerRequest *request){ 

   request->send(200, "text/html", "<html><head><title>ESP32 Live Input</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;} .ButtonStyle{background-color: #4e39c9;border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;font-size: 16px;border: #ffffff 2px solid; border-radius: 20px;}</style></head><body><h1>ESP32 Live Input</h1><p> Send range below to server:</p><input type=\"range\" min=\"0\" max=\"255\" value=\"0\" class=\"slider\" id=\"myRange\" onchange=\"modify()\" ondrag=\"modify()\" on><p>Value: <span id=\"demo\"></span></p><p> Enable: </p><input type=\"checkbox\" id=\"myCheck\" onclick=\"modify()\"><label id=\"myCheck\">on</label><script>var slider = document.getElementById(\"myRange\");var output = document.getElementById(\"demo\");var checkbox = document.getElementById(\"myCheck\");function modify() {output.innerHTML = slider.value;var xhttp = new XMLHttpRequest();xhttp.open(\"POST\", \"/live\", true);xhttp.setRequestHeader(\"Content-type\", \"application/x-www-form-urlencoded\");xhttp.send(\"light=\" + slider.value + \"&LEDEnable=\" + checkbox.value);}</script></body></html>");
});

}
