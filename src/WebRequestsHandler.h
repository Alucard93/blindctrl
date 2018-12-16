#ifndef WEBREQUESTSHANDLER_H
#define WEBREQUESTSHANDLER_H

#include "UpdateHandler.h"
#include "Configuration.h"
#include "WifiSetup.h"
#include "ShutterControl.h"
#include "SetupView.h"
#include "SetupShutter.h"
#include "View.h"
#include "UpdateHandler.h"
#include <ESPAsyncWebServer.h>

class WebRequestsHandler {
private:
  static Configuration* conf;
  static UpdateHandler* uphandler;
  static View* view;
  static AsyncWebServer* ws;

public:

  WebRequestsHandler();
  void setup();
  static void WifiHandler();
  static void handle();
  static void wrHandler(AsyncWebServerRequest *request);
};

#endif
