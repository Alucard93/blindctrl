#include "FunctionView.h"

void FunctionView::slider(Control sender, int type){
//Serial.println(sender.value);
}

void FunctionView::setup(){
  if(!View::_cnf->isFsDone()){
    Serial.println("preparing filesystem");
    ESPUI.prepareFileSystem();
    View::_cnf->setFsDone();
  }
  Serial.println("test connection");
  WifiSetup::connect(View::_cnf->getWifiSSID(),View::_cnf->getWifiPassword());
  Serial.println("connected");
  ESPUI.slider("Slider one", FunctionView::slider, COLOR_ALIZARIN, "30");
  ESPUI.begin("ESPUI Control");
}

void FunctionView::handle(){}
