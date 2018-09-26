#ifndef WIFISETUP_H
#define WIFISETUP_H
#include <WiFi.h>
#include <WiFiClient.h>
class WifiSetup {

private:
  static String av_ap[20];
  static int size;

public:
  static void scanNetworks();
  static void wifiAsAP(const String& wifiName);
  static bool connect(const String& ssid, const String& password);
  static String* getAvailableNetworks();
  static int getNumberOfNetworks();

};
#endif
