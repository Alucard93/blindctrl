#include "WifiSetup.h"

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

WifiSetup::WifiSetup(const Configuration& cnf){
  if(cnf.isConfigured())
    connect(cnf.getWifiSSID(), cnf.getWifiPassword());
  else{
    scanNetworks();
    wifiAsAP();
  }
}

String WifiSetup::wifiAsAP(){
  WiFi.softAP("FirstRun");
  return "FirstRun";
}

bool WifiSetup::connect(const String& ssid, const String& password){
  WiFi.begin(ssid.c_str(), pwd.c_str());
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

  return true;
}

String* WifiSetup::getAvailableNetworks(){
  return av_ap;
}

int WifiSetup::getNumberOfNetworks(){
  return size;
}
