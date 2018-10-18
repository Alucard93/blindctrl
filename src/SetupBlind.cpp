#include "SetupBlind.h"

bool SetupBlind::readyConfigure = false;
//TODO MOVE PIN CONTROL TO BLIND CLASS
void SetupBlind::handleButton(){
    Serial.println(buttonUpStatus);
    Serial.println(buttonDownStatus);
    delay(stdelay);
    if(ready){
        if(buttonUpStatus){
            PinControl::setUpPin();
            if(readyConfigure)
                uptime++;//savetime
        }else if (buttonDownStatus){
            PinControl::setDownPin();
            if(readyConfigure)
                downtime++;//savetime
        }else{
            stop();
        }
    }
}

void SetupBlind::setup(){
    if(View::_cnf->getStage()==1){
        prepareDevice();
        View::_cnf->setStage(2);
    }
    getInterface();
    pinStart();
    ready = true;
}

void SetupBlind::getInterface(){
    ESPUI.button("ready?",readyConf,COLOR_EMERALD,"start");
    ESPUI.button("save and reboot",saveConf,COLOR_EMERALD,"save and reboot");
    ESPUI.begin("test");
    View::serverStart();
}

void SetupBlind::readyConf(Control sender, int type){
    readyConfigure= true;
}

void SetupBlind::saveConf(Control sender, int type){
    View::_cnf->setDownTime(downtime*stdelay);
    View::_cnf->setUpTime(uptime*stdelay);
    View::_cnf->setStage(3);
    delay(stdelay);
    ESP.restart();
}