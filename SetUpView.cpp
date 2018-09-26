#include "SetUpView.h"

String* SetUpView::av_ap=nullptr;
int SetUpView::size=0;
WebServer* SetUpView::_server = new WebServer(80);

void SetUpView::selectWifi() {
  View::_cnf->status();
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
  _server->send(200, "text/html", message);
  View::_cnf->status();

}

void SetUpView::insertPassword(){

  String message = "<!DOCTYPE html><html>";
  if (_server->hasArg("set_ssid")) {
    if (_server->arg("set_ssid") == "true") {
      String ssid = "";
      int choosen = atoi(_server->arg("ssid_id").c_str());
       if (choosen >= 0)
        ssid = av_ap[choosen];
       else
        ssid = "to define";
      message += "INERT PASSWORD FOR " + ssid +"<br>";
      View::_cnf->setWifiSSID(ssid);
    }
    message += "<form action='/pwdns' method='post'>";
    message += "<input type=\"hidden\" name = \"set_pwd\" value=\"true\">";
    message += "<input type='password' name='pwd'>";
    message += "<br><input type=\"submit\" value=\"Submit\">";
    message += "</form></div>";
    message += "</html>";
    _server->send(200, "text/html", message);
    View::_cnf->status();
  }else{
    //redirect("error");
  }

}
void SetUpView::getApi(){
  String message = "<!DOCTYPE html><html>";
  if (_server->hasArg("set_pwd")) {
    if (_server->arg("set_pwd") == "true") {
      String pwd = _server->arg("pwd");
      message += "PASSWORD WAS " + pwd +"<br> API KEY <br>";
      View::_cnf->setWifiPassword(pwd);
      View::_cnf->setNewApiKey();
    }
    message += View::_cnf->getApiKey();
    _server->send(200, "text/html", message);
    View::_cnf->setConfigured();
    View::_cnf->status();
  }else{
    //redirect("error");
  }
}

void SetUpView::error(){
  _server->send(400, "text/html", "bad request");
}

void SetUpView::reboot(){
  ESP.restart();
}

void SetUpView::setup(){
  WifiSetup::scanNetworks();
  av_ap = WifiSetup::getAvailableNetworks();
  size = WifiSetup::getNumberOfNetworks();
  WifiSetup::wifiAsAP("setup");
  View::_cnf->reset();
  _server->on("/", selectWifi);
  _server->on("/wfsl", insertPassword);
  _server->on("/pwdns", getApi);
  _server->on("/error", error);
  _server->on("/reboot", reboot);
  _server->begin();
}

void SetUpView::handle(){
  _server->handleClient();
}
