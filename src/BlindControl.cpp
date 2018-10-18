#include "BlindControl.h"

int BlindControl::status = 0;
long int BlindControl::time=0;
int BlindControl::pinToUse=2;
bool Blind::free=true;


/**
 * 
 * 
 * 
 * */
void BlindControl::move(){
    Serial.println(pinToUse);    
    pinMode(pinToUse, OUTPUT);
    if( (time - 500) < 0){
        time = 0;
        digitalWrite(pinToUse, HIGH);
        pinToUse = 2;
        digitalWrite(pinToUse, HIGH);
    }
    else{
        digitalWrite(pinToUse, LOW);
        time -= 500;
    }
    Serial.println(digitalRead(pinToUse));
    Serial.println(time);


}

void BlindControl::handleRequest(Control sender, int type){
    int requested_status = atoi(sender.value.c_str());
    setStatus(requested_status);
}

void BlindControl::resetFunction(Control sender, int type){
    View::_cnf->reset();
    ESP.restart();
}


void BlindControl::setup(){
    Serial.println("setUp");
    uptime = View::_cnf->getUpTime();
    downtime = View::_cnf->getDownTime();
    wifisetup();
    getControlInteraface();
    ready = true;
}

void BlindControl::getControlInteraface(){
    Serial.println("gui setup");
    Serial.println("gui setup");
    ESPUI.slider("Controller", handleRequest, COLOR_ALIZARIN, String(status));
    ESPUI.button("",resetFunction, COLOR_ALIZARIN, "reset button");
    ESPUI.begin("Blinder Control");
    this->pinStart();
}

void BlindControl::handleButton(){
    Serial.println(status);
    delay(250);
    if(ready){
        move();        
        if(View::_cnf->isFsDone()){
            if(buttonUpStatus)
                setStatus(status-1);
            else if(buttonDownStatus)
                setStatus(status+1);
            else
                free = true;
        }
    }
    
}


void BlindControl::setStatus(int l_status){
    if(l_status>=0 && l_status<=100){
        Serial.println(status);
        int timetoSet;
        if((buttonUpStatus || buttonDownStatus) && free)
        {
            time = 0 ;
            stop();
            free = false ;
        }
        if(l_status<status){
            if(free)
                timetoSet = (uptime/100)*(status-l_status);
            else
                timetoSet = 500;
            if(pinToUse == downPin && time!=0){
                time = abs(time - timetoSet);
                stop();
            }
            else
                time += timetoSet;
            pinToUse = upPin;
        }
        else if(l_status>status){
            if(free)
                timetoSet = (downtime/100)*(l_status-status);
            else
                timetoSet = 500;
            if(pinToUse == upPin && time !=0){
                time = abs(time - timetoSet);
                stop();
                }
            else
                time += timetoSet;
            pinToUse = downPin;
        }
        status = l_status;
        ESPUI.updateSlider(0, status);
    }

}