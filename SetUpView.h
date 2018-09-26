#ifndef SETUPVIEW_H
#define SETUPVIEW_H

#include "View.h"
#include "WifiSetup.h"
#include <ESPAsyncWebServer.h>
//#include <ESPAsyncTCP.h>

class SetUpView : public View{
private:
  static String* av_ap;
  static int size;
  static AsyncWebServer server;
  static void selectWifi(AsyncWebServerRequest *request);
  static void insertPassword(AsyncWebServerRequest *request);
  static void getApi(AsyncWebServerRequest *request);
  static void error(AsyncWebServerRequest *request);
  static void reboot(AsyncWebServerRequest *request);
public:
  SetUpView(Configuration& cnf):View(cnf){}
  void setup();
  void handle();
};

#endif
