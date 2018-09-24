#include "Configs.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Preferences.h>

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

class FirstRun{
  private:
    static WebServer* server;
    static Configs cnf;
    static String av_ap[20];
    static int size;

  public:
    FirstRun();
    static void DefineResponses();
    static void SelectWifi();
    static void InsertPassword();
    static void getApi();
    static void error();
    static void reboot();
    static void redirect(String path);
    static void wifiAsAP();
    static WebServer* getServer();
    ~FirstRun();
};

#endif CONNECTIONHANDLER_H
