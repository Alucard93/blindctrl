#ifndef SETUPVIEW_H
#define SETUPVIEW_H

#include "View.h"
#include "WifiSetup.h"
#include <WebServer.h>

class SetUpView : public View{
private:
  static String* av_ap;
  static int size;
  static WebServer* _server;
  static void selectWifi();
  static void insertPassword();
  static void getApi();
  static void error();
  static void reboot();
public:
  SetUpView(Configuration& cnf):View(cnf){}
  void setup();
  void handle();
};

#endif
