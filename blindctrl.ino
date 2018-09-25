#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Preferences.h>

Preferences pref;
//FIELDS CONF
const char* name_mem = "BLNDR_CNF";
const char* ssid_key = "ssid";
const char* password_key = "pwd";
const char* api_key = "api";
const char* configured_key = "cnf";

//CONFSETUP
bool configured;

String on_path;
String off_path;

int ledstatus = 0;

WebServer server(80);

const int led = 2;

void printStatsTerminal(){
  Serial.print("SSID: ");
  Serial.println(pref.getString(ssid_key,"not set").c_str());
  Serial.print("PWD: ");
  Serial.println(pref.getString(password_key,"not set").c_str());
  Serial.print("API: ");
  Serial.println(pref.getString(api_key,"not set").c_str());
}

String newKey(){
  String toReturn = "";
  for (int i = 0 ; i < 30; i++) {
    byte randomValue = random(0, 37);
    char letter = randomValue + 'a';
    if (randomValue > 26)
      letter = (randomValue - 26) + '0';
  toReturn+=letter;
}
return toReturn;
}

void handleNormal() {
    server.send(200, "text/html", "yeah");
}

void selectWifi() {
  String message = "";
  message += "<!DOCTYPE html>";
  message += "<html>";
  message += "<div>SELECT SSID<br>";
  message += "<form action='/wfsl' method='post'>";
  message += "<input type=\"hidden\" name = \"set_ssid\" value=\"true\">";
  for (int i = 0; i < size; i++) {
    message += "<input type=\"radio\" name = \"ssid_id\" value=\"";
    message += i;
    message += "\">";
    message += av_ap[i].c_str();
    message += "<br>";
  }
  message += "<input type=\"radio\" name = \"ssid_id\" value='-1'>Not listed<br>";
  message += "<br><input type=\"submit\" value=\"Submit\">";
  message += "</form></div>";
  message += "</html>";

  server.send(200, "text/html", message);
  printStatsTerminal();
}

void insertPassword(){

  String message = "<!DOCTYPE html><html>";
  if (server.hasArg("set_ssid")) {
    if (server.arg("set_ssid") == "true") {
      String ssid = "";
      int choosen = atoi(server.arg("ssid_id").c_str());
       if (choosen >= 0)
        ssid = av_ap[choosen];
       else
        ssid = "to define";
      message += "INERT PASSWORD FOR " + ssid +"<br>";
      pref.putString(ssid_key,ssid);
    }
    message += "<form action='/pwdns' method='post'>";
    message += "<input type=\"hidden\" name = \"set_pwd\" value=\"true\">";
    message += "<input type='password' name='pwd'>";
    message += "<br><input type=\"submit\" value=\"Submit\">";
    message += "</form></div>";
    message += "</html>";
    server.send(200, "text/html", message);
    printStatsTerminal();
  }else{
    //redirect("error");
  }

}
void getApi(){
  String message = "<!DOCTYPE html><html>";
  if (server.hasArg("set_pwd")) {
    if (server.arg("set_pwd") == "true") {
      String pwd = server.arg("pwd");
      message += "PASSWORD WAS " + pwd +"<br> API KEY <br>";
      String k = newKey();
      Serial.println(k.c_str());
      pref.putString(password_key,pwd);
      pref.putString(api_key, newKey());
    }
    message += pref.getString(api_key);
    server.send(200, "text/html", message);
    pref.putBool(configured_key,true);
    printStatsTerminal();
    pref.end();
  }else{
    //redirect("error");
  }
}

void error(){
  server.send(400, "text/html", "bad request");
}

void reboot(){
  ESP.restart();
}


bool wifiAsClient(const String& ssid, const String& pwd) {
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

void wifiAsAP() {
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
  WiFi.softAP("FirstRun");
  Serial.println(WiFi.softAPIP());
}

void configResponses() {
  server.on("/", selectWifi);
  server.on("/wfsl", insertPassword);
  server.on("/pwdns", getApi);
  server.on("/error", error);
  server.on("/reboot", reboot);
  server.begin();
}

void setup(void) {
  Serial.begin(115200);
  pref.begin(name_mem,true);
  String ssid = pref.getString(ssid_key,"not set");
  String pwd = pref.getString(password_key,"not set");
  printStatsTerminal();
  configured = pref.getBool(configured_key);
  pref.end();
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  if (configured && wifiAsClient(ssid,pwd)) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid.c_str());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.on("/", handleNormal);
    server.begin();
    Serial.println("HTTP server started");
  }else{
    pref.begin(name_mem,false);
    pref.clear();
    wifiAsAP();
    configResponses();
  }
  Serial.println(WiFi.softAPIP());
  if (MDNS.begin("esp32.local"))
    Serial.println("MDNS responder started");
}

void loop(void) {
  server.handleClient();
}
