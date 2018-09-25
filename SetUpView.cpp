#include "SetUpView.h"

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
  _server.send(200, "text/html", message);

}

void insertPassword(){

  String message = "<!DOCTYPE html><html>";
  if (_server.hasArg("set_ssid")) {
    if (_server.arg("set_ssid") == "true") {
      String ssid = "";
      int choosen = atoi(_server.arg("ssid_id").c_str());
       if (choosen >= 0)
        ssid = av_ap[choosen];
       else
        ssid = "to define";
      message += "INERT PASSWORD FOR " + ssid +"<br>";
      _cnf.setWifiSSID(ssid);
    }
    message += "<form action='/pwdns' method='post'>";
    message += "<input type=\"hidden\" name = \"set_pwd\" value=\"true\">";
    message += "<input type='password' name='pwd'>";
    message += "<br><input type=\"submit\" value=\"Submit\">";
    message += "</form></div>";
    message += "</html>";
    _server.send(200, "text/html", message);
  }else{
    //redirect("error");
  }

}
void getApi(){
  String message = "<!DOCTYPE html><html>";
  if (_server.hasArg("set_pwd")) {
    if (_server.arg("set_pwd") == "true") {
      String pwd = _server.arg("pwd");
      message += "PASSWORD WAS " + pwd +"<br> API KEY <br>";
      String k = newKey();
      Serial.println(k.c_str());
      _cnf.setWifiPassword(pwd);
      _cnf.setNewApiKey();
    }
    message += _cnf.getApiKey();
    _server.send(200, "text/html", message);
    _cnf.setConfigured(true);
  }else{
    //redirect("error");
  }
}

void error(){
  _server.send(400, "text/html", "bad request");
}

void reboot(){
  ESP.restart();
}

void setup(){
  _server.on("/", selectWifi);
  _server.on("/wfsl", insertPassword);
  _server.on("/pwdns", getApi);
  _server.on("/error", error);
  _server.on("/reboot", reboot);
  _server.begin();
}
