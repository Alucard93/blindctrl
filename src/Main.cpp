#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "WebRequestsHandler.h"
#include <RemoteDebug.h>

WebRequestsHandler* handler;
RemoteDebug* Debug;

TaskHandle_t Connection;

void setup(void) {
  Serial.begin(115200);
  Debug = new RemoteDebug();
  Debug->begin("ShutterController");
  Debug->setSerialEnabled(true);
  Debug->setResetCmdEnabled(true);
  handler = new WebRequestsHandler();
  handler->setup();
  //Serial.println(WiFi.localIP());
  MDNS.begin("ShutterController");

}

void loop(void) {
  WebRequestsHandler::WifiHandler();
  WebRequestsHandler::handle();
  Debug->handle();
}
