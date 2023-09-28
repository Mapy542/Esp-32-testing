#include <ESPAsyncWebServer.h>

void AddServerPages(AsyncWebServer &server){
server.onNotFound([](AsyncWebServerRequest *request){ 
   request->send(404, "text/html", "<html><head><title>you done messed up b-lak-ae</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}button{background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;border: 2px solid #2200aa;border-radius: 5px;}</style></head><body><h1>404...</h1><p> No content here</p><p> Go back <a href = \"/\">home. </a></p><a href=\"/\"><button>Click me</button></a></html>");
});

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}</style></head><body><h1>ESP - 32</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#000000\"><p>Go to <a href = \"/light\">light update.</a></p><p> Try on a better <a href=\"https://kentstatesucks.gozips.com\"> domain</a> for size.</p><table><tr><td> <a href=\"/hello\"> Goto hard coded page.</a></td></tr><tr><td><a href = \"/404me\"> Errors Am I right</a> </td></tr></table></body></html>");
});

server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", "<html><head><title>ESP - 32</title><style>body {background-color: #ffffff;color: #2200aa;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;} </style></head><body><h1>ESP - 32</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#000000\"><form method=\"post\" action=\"/light\" enctype=\'multipart/form-data\'><p> Set Light Delay (0-1000 ms)</p><input type=\"text\" name=\"light\" value=\"0\"> <br><input type=\"submit\" value=\"Submit\"></form></body></html>");
});

server.on("/page", HTTP_GET, [](AsyncWebServerRequest *request){ 
   request->send(200, "text/html", "<html><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width\"><title>Wifi Test</title><style>body {background-color: #000000;color: #00ff00;font-family: \"Courier New\", Courier, monospace;font-size: 1em;text-align: center;}</style></head><body><h1>UA Robotics</h1><p>Those semi-conductors never stood a chance...</p><hr color=\"#00ff00\"><p> <a href=\"/hello\"> Goto hard coded page.</a></p><p><a href=\"http://kentstatesucks.gozips.com\">Try a new domain on</a></p></body></html>");
});

}
