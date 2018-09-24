#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "FirstRun.h"
#include "Configs.h"

Configs cnf;
const char* ssid;
const char* pwd;
bool configured;

String on_path;
String off_path;
String av_ap[20];
int found_ap;
int ledstatus = 0;

WebServer* server = NULL;
FirstRun* first = NULL;

const int led = 2;

void handleNormal() {
    server->send(200, "text/html", "yeah");
}

void wifiAsClient() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

}

void setup(void) {
  cnf.begin();
  ssid = cnf.getSSID();
  pwd = cnf.getPassword();
  configured = cnf.isConfigured();
  Serial.begin(115200);
  Serial.println(ssid);
  Serial.println(pwd);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  if (configured) {
    wifiAsClient();
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32.local")) {
    Serial.println("MDNS responder started");
  }

  if (configured){
    server->on("/", handleNormal);
    server->begin();
    Serial.println("HTTP server started");
  }
  else{
    first = new FirstRun();
    server = first->getServer();
  }
}

void loop(void) {
  server->handleClient();
}
