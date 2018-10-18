#ifndef VIEW_H
#define VIEW_H

#include "Configuration.h"
#include <time.h>
#include <ESPAsyncWebServer.h>

class View{
protected:
  static Configuration* _cnf;
  static AsyncWebServer* webServer;
public:
  View(Configuration& cnf);
  static void pageError(AsyncWebServerRequest *request);
  static void reboot(AsyncWebServerRequest *request);
  static void reset(AsyncWebServerRequest *request);
  static void serverStart();
  virtual ~View() = default;
  virtual void handleButton() =0;
  virtual void setup() = 0;
};

#endif