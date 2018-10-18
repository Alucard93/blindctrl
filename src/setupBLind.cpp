#include "setupBlind.h"

bool setupBlind::readyConfigure = false;

void setupBlind::handleButton(){
    delay(stdelay);
    if(ready){
        if(buttonUpStatus){
            digitalWrite(upPin, LOW);
            digitalWrite(downPin, HIGH);
            if(readyConfigure)
                uptime++;//savetime
        }else if (buttonDownStatus){
            digitalWrite(downPin, LOW);
            digitalWrite(upPin, HIGH);
            if(readyConfigure)
                downtime++;//savetime
        }else{
            stop();
        }
    }
}

void setupBlind::setup(){
    if(View::_cnf->getStage()==1)
    pinStart();
    wifisetup();
}

void setupBlind::getInterface(){
    ESPUI.print("","prepare to configure the device bring the blind all the way up");
    ESPUI.button("ready?",readyConf,COLOR_EMERALD,"start");
    ESPUI.button("save and reboot",saveConf,COLOR_EMERALD,"save and reboot");
    ESPUI.begin("Configure BlindController");
}

void setupBlind::readyConf(Control sender, int type){
    readyConfigure= true;
}

void setupBlind::saveConf(Control sender, int type){
    View::_cnf->setDownTime(downtime);
    View::_cnf->setUpTime(uptime);
    delay(stdelay);
    ESP.restart();
}