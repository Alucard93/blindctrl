#include "SetupShutter.h"

int SetupShutter::configureUp = 0;
int SetupShutter::configureDown = 0;
//TODO MOVE PIN CONTROL TO Shutter CLASS
void SetupShutter::handleButton(){
    if(ready){
        if(buttonUpStatus){
            PinControl::setUpPin();
            if(configureUp == 1){
                uptime = millis();
                configureUp++;
            }//savetime
        }else if (buttonDownStatus){
            PinControl::setDownPin();
            if(configureDown == 1){
                downtime=millis();//savetime
                configureDown++;
            }
        }else{
            if(configureUp == 2){
                uptime = millis() - uptime;
                configureUp = 0;
            }
            if(configureDown == 2){
                downtime = millis() - downtime;
                configureDown = 0;
            }
            stop();
        }
    }
}

void SetupShutter::setup(){
    if(View::_cnf->getStage()==1){
        ESPUI.prepareFileSystem();
        View::_cnf->setStage(2);
    }
    getInterface();
    pinStart();
    ready = true;
    PinControl::readyLed(true);
}

void SetupShutter::getInterface(){
    ESPUI.button("Up",upConf,COLOR_EMERALD,"Configure UP");
    ESPUI.button("Down",downConf,COLOR_EMERALD,"Configure DOWN");
    ESPUI.button("save and reboot",saveConf,COLOR_EMERALD,"save and reboot");
    ESPUI.begin("test");
    View::serverStart();
}

void SetupShutter::upConf(Control sender, int type){
    configureUp= 1;
}

void SetupShutter::downConf(Control sender, int type){
    configureDown= 1;
}

void SetupShutter::saveConf(Control sender, int type){
    View::_cnf->setDownTime(downtime);
    View::_cnf->setUpTime(uptime);
    View::_cnf->setStage(3);
    //ESP.restart();
    Serial.println(downtime);
    Serial.println(uptime);
}
