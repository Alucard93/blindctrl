#include "WifiSetup.h"

WiFiClient WifiSetup::wifiClient;
String WifiSetup::av_ap[20]={};
int WifiSetup::size=0;
painlessMesh WifiSetup::mesh;

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
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 11);
  mesh.stationManual(ssid, password);
  mesh.setHostname("prova");

  return true;
}

String* WifiSetup::getAvailableNetworks(){
  return av_ap;
}

int WifiSetup::getNumberOfNetworks(){
  return size;
}

void WifiSetup::updateMesh(){
    mesh.update();
}
