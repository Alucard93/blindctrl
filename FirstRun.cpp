#include "FirstRun.h";

WebServer* FirstRun::server = new WebServer(80);
Configs FirstRun::cnf;
String FirstRun::av_ap[20];
int FirstRun::size;

FirstRun::FirstRun(){
  cnf.begin();
  cnf.reset();
  wifiAsAP();
  DefineResponses();
}

void FirstRun::DefineResponses() {
  server->on("/", FirstRun::SelectWifi);
  server->on("/wfsl", FirstRun::InsertPassword);
  server->on("/pwdns", FirstRun::getApi);
  server->on("/error", FirstRun::error);
  server->on("/reboot", FirstRun::reboot);
  server->begin();
}

void FirstRun::SelectWifi() {
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

  server->send(200, "text/html", message);
}

void FirstRun::InsertPassword(){

  String message = "<!DOCTYPE html><html>";
  if (server->hasArg("set_ssid")) {
    if (server->arg("set_ssid") == "true") {
      String ssid = "";
      int choosen = atoi(server->arg("ssid_id").c_str());
       if (choosen >= 0)
        ssid = av_ap[choosen];
       else
        ssid = "to define";
      message += "INERT PASSWORD FOR " + ssid +"<br>";
      cnf.setSSID(ssid);
    }
    message += "<form action='/pwdns' method='post'>";
    message += "<input type=\"hidden\" name = \"set_pwd\" value=\"true\">";
    message += "<input type='password' name='pwd'>";
    message += "<br><input type=\"submit\" value=\"Submit\">";
    message += "</form></div>";
    message += "</html>";
    server->send(200, "text/html", message);
  }else{
    redirect("error");
  }

}
void FirstRun::getApi(){
  String message = "<!DOCTYPE html><html>";
  if (server->hasArg("set_pwd")) {
    if (server->arg("set_pwd") == "true") {
      String pwd = server->arg("pwd");
      message += "PASSWORD WAS " + pwd +"<br> API KEY <br>";
      cnf.setPassword(pwd);
      cnf.setKey();
    }
    message += cnf.getApiKey();
    server->send(200, "text/html", message);
    cnf.setConfigured();
    cnf.end();
  }else{
    redirect("error");
  }
}

void FirstRun::error(){
  server->send(400, "text/html", "bad request");
}

void FirstRun::reboot(){
  ESP.restart();
}

void FirstRun::redirect(String path){
  server->sendHeader("Location", String("/"+path), true);
  server->send ( 302, "text/plain", "");
}

void FirstRun::wifiAsAP() {
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

WebServer* FirstRun::getServer(){
  Serial.println("getServer");
  return server;
}

FirstRun::~FirstRun(){
  server->stop();
}
