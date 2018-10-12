#include "WifiSetup.h"

String WifiSetup::av_ap[20]={};
int WifiSetup::size=0;

void WifiSetup::scanNetworks(){
  WiFi.mode(WIFI_STA);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(WiFi.SSID(i));
      av_ap[i] = WiFi.SSID(i);
      delay(10);
    }
    size = n;
  }
}

void WifiSetup::wifiAsAP(const String& wifiName){
  WiFi.softAP(wifiName.c_str());
}

bool WifiSetup::connect(const String& ssid, const String& password){
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid.c_str(), password.c_str());
    int retry = 40;
    while (WiFi.status() != WL_CONNECTED && retry >= 0) {
      delay(500);
      Serial.print(".");
      retry--;
    }
    if(retry==0){
      Serial.println("error");
      return false;
    }
  }
  return true;
}

String* WifiSetup::getAvailableNetworks(){
  return av_ap;
}

int WifiSetup::getNumberOfNetworks(){
  return size;
}
