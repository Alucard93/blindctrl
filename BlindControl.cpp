#include "BlindControl.h"

bool BlindControl::free = true;
int BlindControl::status = 0;
int BlindControl::buttonUpStatus = 0;
int BlindControl::buttonDownStatus = 0;
bool BlindControl::ready = false;

void BlindControl::blinderUp(){
    buttonUpStatus=digitalRead(buttonUp);
}

void BlindControl::blinderUp(int up){
    if(status>0){
        free = false;
        digitalWrite(upPin, HIGH);
        delay(unit*up);
        digitalWrite(upPin, LOW);
        status -= up; 
        free = true;
        }
}

void BlindControl::blinderDown(){
    buttonDownStatus = digitalRead(buttonDown);
}

void BlindControl::blinderDown(int down){
    if(status<100){
        free = false;
        digitalWrite(downPin, HIGH);
        delay(unit*down);
        digitalWrite(downPin, LOW);
        status += down;
        free = true;
    }
}
void BlindControl::handleRequest(Control sender, int type){
    while (!free){
        delay(3000);
    }
    int requested_status = atoi(sender.value.c_str());
    if(requested_status>status)
        blinderDown(requested_status-status);
    else if (requested_status<status)
        blinderUp(status-requested_status);
    View::_cnf->setStatus(String(status));
}
void BlindControl::setup(){
    Serial.println("setUp");
    wifisetup();
    pinMode(upPin, OUTPUT);
    pinMode(downPin, OUTPUT);
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
    attachInterrupt(digitalPinToInterrupt(buttonUp),blinderUp,RISING);
    attachInterrupt(digitalPinToInterrupt(buttonDown),blinderDown,RISING);
    if(View::_cnf->getStatus() == "")
        status = 0;
    else
        status = atoi(View::_cnf->getStatus().c_str());
    getControlInteraface();
    ready = true;
}

void BlindControl::getControlInteraface(){
    Serial.println("gui setup");
    ESPUI.slider("Controller", handleRequest, COLOR_ALIZARIN, String(status));
    ESPUI.begin("Blinder Control");
}

void BlindControl::wifisetup(){
    
  if(!View::_cnf->isFsDone()){
    Serial.println("preparing filesystem");
    ESPUI.prepareFileSystem();
    View::_cnf->setFsDone();
  }
  Serial.println("test connection");
  WifiSetup::connect(View::_cnf->getWifiSSID(),View::_cnf->getWifiPassword());
}

void BlindControl::handleButton(){
    if(ready){
        if(buttonUpStatus){
            blinderUp(1);
            ESPUI.updateSlider(0, status);
        }
        if(buttonDownStatus){
            blinderDown(1);
            ESPUI.updateSlider(0, status);
        }
    }
}