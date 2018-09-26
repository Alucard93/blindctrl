#include <ESPmDNS.h>
#include "WebRequestsHandler.h"
WebRequestsHandler* handler;

void setup(void) {
  Serial.begin(115200);
  WebRequestsHandler* handler = new WebRequestsHandler();
  handler->setup();
  Serial.println(WiFi.softAPIP());
}

void loop(void) {
  handler->handle();
}
