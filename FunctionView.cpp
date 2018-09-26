#include "FunctionView.h"

void FunctionView::slider(Control sender, int type){
//Serial.println(sender.value);
}

void FunctionView::setup(){
  if(!View::_cnf->isFsDone()){
    ESPUI.prepareFileSystem();
    delay(20000);
    View::_cnf->setFsDone();
  }
  WifiSetup::connect(View::_cnf->getWifiSSID(),View::_cnf->getWifiPassword());
  //ESPUI.slider("Slider one", FunctionView::slider, COLOR_ALIZARIN, "30");
  //ESPUI.begin("ESPUI Control");
}

void FunctionView::handle(){
  delay(20000);
  Serial.println("pen");
  /**if (millis() - oldTime > 5000) {
    ESPUI.print("Millis:", String(millis()));
    switchi = !switchi;
    ESPUI.updateSwitcher("Switch one", switchi);
    oldTime = millis();
  }**/
}
