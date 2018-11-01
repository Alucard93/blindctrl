#include "WebRequestsHandler.h"

View* WebRequestsHandler::view;
AsyncWebServer* WebRequestsHandler::ws;
UpdateHandler* WebRequestsHandler::uphandler;
Configuration* WebRequestsHandler::conf;

WebRequestsHandler::WebRequestsHandler(){
  conf = new Configuration();
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

void WebRequestsHandler::wrHandler(AsyncWebServerRequest *request){
  WebRequestsHandler::conf->reset();
  ESP.restart();
}

void WebRequestsHandler::setup(){
  if(conf->getStage())
    WifiSetup::connect(conf->getWifiSSID(),conf->getWifiPassword());
  view->setup();
  if(!conf->getStage())
    WifiSetup::wifiAsAP("setup");

  ws = new AsyncWebServer(91);
  ws->on("/", HTTP_ANY, wrHandler);
  ws->begin();
  uphandler = new UpdateHandler();
  PinControl::ready = true;

}

void WebRequestsHandler::handle(){
    PinControl::hwButton();
    view->handleButton();
    uphandler->handle();
}
