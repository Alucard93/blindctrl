#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "WebRequestsHandler.h"
#include "UpdaterHandler.h"
WebRequestsHandler* handler;
UpdateHandler* uphandler;

void setup(void) {
  Serial.begin(115200);  
  handler = new WebRequestsHandler();
  handler->setup();
  Serial.println(WiFi.softAPIP());
  uphandler = new UpdateHandler();
}

void loop(void) {
  WebRequestsHandler::handle();
  UpdateHandler::handle();
}
