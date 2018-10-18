#include "SetupView.h"

String* SetupView::av_ap=nullptr;
int SetupView::size=0;

void SetupView::handler(AsyncWebServerRequest *request) {
  int headers = request->headers();
  int i;
  for(i=0;i<headers;i++){
    Serial.printf("HEADER[%s]: %s\n", request->headerName(i).c_str(), request->header(i).c_str());
  }
  //List all parameters
  int params = request->params();
  for(int i=0;i<params;i++){
    AsyncWebParameter* p = request->getParam(i);
    if(p->isFile()){ //p->isPost() is also true
      Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
    } else if(p->isPost()){
      Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
    } else {
      Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
    }
  }
  String toUse = "<!DOCTYPE html><html><header><title>First configuration</title></header><body>";

  if(request->hasParam("set_ssid", true)){
    toUse = getWifiPasswordInsertionScreen(request->getParam("ssid_id", true)->value());
  }else if (request->hasParam("set_pwd",true)){
    toUse = getSuccessScreen(request->getParam("pwd",true)->value());
  }
  else
    toUse = getWifiSelectionScreen();

  toUse += "</body></html>";
  request->send(200, "text/html", toUse);

}

String SetupView::getWifiSelectionScreen(){
  String message = "";
  message += "<div>SELECT SSID<br>";
  message += "<form action='/' method='post'>";
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
  return message;
}

String SetupView::getWifiPasswordInsertionScreen(String ssid_id){
  String message = "";
  String ssid;
  int choosen = atoi(ssid_id.c_str());
  if (choosen >= 0)
    ssid = av_ap[choosen];
  else
    ssid = "to define";
  message += "INERT PASSWORD FOR " + ssid +"<br>";
  View::_cnf->setWifiSSID(ssid);
  message += "<form action='/' method='post'>";
  message += "<input type=\"hidden\" name = \"set_pwd\" value=\"true\">";
  message += "<input type='password' name='pwd'>";
  message += "<br><input type=\"submit\" value=\"Submit\">";
  message += "</form></div>";
  message += "</html>";
  return message;
}

String SetupView::getSuccessScreen(String pwd){
  String message;
  message += "PASSWORD WAS " + pwd +"<br> API KEY <br>";
  View::_cnf->setWifiPassword(pwd);
  View::_cnf->setNewApiKey();
  message += View::_cnf->getApiKey();
  View::_cnf->setStage(1);
  return message;
}

void SetupView::setup(){
  WifiSetup::scanNetworks();
  av_ap = WifiSetup::getAvailableNetworks();
  size = WifiSetup::getNumberOfNetworks();
  View::_cnf->reset();
  View::serverStart();
  webServer->on("/", HTTP_ANY,handler);
  webServer->begin();
}

void SetupView::handleButton(){
  
}