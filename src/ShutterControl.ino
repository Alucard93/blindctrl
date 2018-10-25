#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "WebRequestsHandler.h"

WebRequestsHandler* handler;

void setup(void) {
  Serial.begin(115200);  
  handler = new WebRequestsHandler();
  handler->setup();
  Serial.println(WiFi.softAPIP());
  MDNS.begin("ShutterController");
}

void loop(void) {
  WebRequestsHandler::handle();
}
