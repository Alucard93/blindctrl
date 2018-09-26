#include "FunctionView.h"

void FunctionView::slider(Control sender, int type){
//Serial.println(sender.value);
}

void FunctionView::setup(){
  Serial.println("test connection");
  WifiSetup::connect(View::_cnf->getWifiSSID(),View::_cnf->getWifiPassword());
  Serial.println("connected");
  ESPUI.slider("Slider one", FunctionView::slider, COLOR_ALIZARIN, "30");
  ESPUI.begin("ESPUI Control");
}

void FunctionView::handle(){}
