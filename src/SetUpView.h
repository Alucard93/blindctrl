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
  static void handler(AsyncWebServerRequest *request);
  static void error(AsyncWebServerRequest *request);
  static void reboot(AsyncWebServerRequest *request);
  static String getWifiSelectionScreen();
  static String getWifiPasswordInsertionScreen(String ssid_id);
  static String getSuccessScreen(String pwd);
public:
  SetUpView(Configuration& cnf):View(cnf){}
  void setup();
  void handleButton();
};

#endif
