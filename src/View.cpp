#include "View.h"

Configuration* View::_cnf;
AsyncWebServer* View::webServer;

View::View(Configuration& cnf){
    _cnf = (&cnf);
}

void View::serverStart(){
    webServer = new AsyncWebServer(80);
    webServer->on("/error", HTTP_ANY,pageError);
    webServer->on("/reboot", HTTP_ANY,reboot);
    webServer->on("/reset", HTTP_ANY,reset);
}

void View::pageError(AsyncWebServerRequest *request){
    request->send(400, "text/html", "bad request");
}

void View::reboot(AsyncWebServerRequest *request){
    ESP.restart();
}

void View::reset(AsyncWebServerRequest *request){
    request->send(200, "text/html", "all deleted rebooting");
    _cnf->reset();
    delay(500);
    ESP.restart();
}