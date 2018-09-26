#include <ESPmDNS.h>
#include "WebRequestsHandler.h"
WebRequestsHandler* handler;

void setup(void) {
  Serial.begin(115200);
  WebRequestsHandler* handler = new WebRequestsHandler();
  handler->setup();
  Serial.println(WiFi.softAPIP());
  if (MDNS.begin("esp32.local"))
    Serial.println("MDNS responder started");
}

void loop(void) {
  handler->handle();
}
