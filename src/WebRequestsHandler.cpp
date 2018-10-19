#include "WebRequestsHandler.h"

View* WebRequestsHandler::view;


WebRequestsHandler::WebRequestsHandler(){
  conf = new Configuration();
  int stage = conf->getStage();
  switch(conf->getStage()){
    case 0: 
      view = new SetupView(*conf);
      Serial.println("SetupView");      
      break;
  case 1:
  case 2:
      view = new SetupShutter(*conf);
      Serial.println("SetupBlind");
      break;
  case 3:
      view = new ShutterControl(*conf);
      Serial.println("BlindControl");     
      break;
  }
}

void WebRequestsHandler::setup(){
  if(conf->getStage())
    WifiSetup::connect(conf->getWifiSSID(),conf->getWifiPassword());
  view->setup();
  if(!conf->getStage())
    WifiSetup::wifiAsAP("setup");
}

void WebRequestsHandler::handle(){
  view->handleButton();
}