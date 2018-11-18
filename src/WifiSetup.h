#ifndef WIFISETUP_H
#define WIFISETUP_H
#include <WiFi.h>
#include <WiFiClient.h>
#include <painlessMesh.h>

#define   MESH_PREFIX     "shtctrl"
#define   MESH_PASSWORD   "shtctrlPW"
#define   MESH_PORT       5555

class WifiSetup {

private:
    static WiFiClient wifiClient;
    static String av_ap[20];
    static int size;
    static painlessMesh mesh;

public:
    static void scanNetworks();
    static void wifiAsAP(const String& wifiName);
    static bool connect(const String& ssid, const String& password);
    static String* getAvailableNetworks();
    static int getNumberOfNetworks();
    static void updateMesh();

};
#endif
