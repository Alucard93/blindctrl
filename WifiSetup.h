#ifndef WIFISETUP_H
#define WIFISETUP_H
#include <WiFi.h>
#include <WiFiClient.h>
class WifiSetup {

private:
  String av_ap[20];
  int size;
  void scanNetworks();

public:
  WifiSetup(bool configured);
  String wifiAsAP();
  bool connect(const String& ssid, const String& password);
  String* getAvailableNetworks();
  int getNumberOfNetworks();

};
#endif
