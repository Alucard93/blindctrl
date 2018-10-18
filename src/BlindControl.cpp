#include "BlindControl.h"

int BlindControl::status = 0;
long int BlindControl::time=0;
int BlindControl::pinToUse=0;
bool PinControl::free=true;


/**
 * @brief BlindControl::move checks that time is 0 
 * */
void BlindControl::move(){
    Serial.println(pinToUse);    
    if(pinToUse == 0)
        stop();
    if(pinToUse == -1)
        setDownPin();
    if(pinToUse == 1)
        setDownPin();
    if( (time - 500) < 0){
        time = 0;
        pinToUse = 0;
    }
    else{
        time -= 500;
    }
    Serial.println(time);


}

/**
 * @brief BlindControl::handleRequest handles the request from the slider
 * */
void BlindControl::handleRequest(Control sender, int type){
    int requested_status = atoi(sender.value.c_str());
    setStatus(requested_status);
}


/**
 * @brief BlindControl::setup() prepare the device already configured
 * */
void BlindControl::setup(){
    Serial.println("setUp");
    uptime = View::_cnf->getUpTime();
    downtime = View::_cnf->getDownTime();
    getControlInteraface();
}
 
 /**
  * @brief BlindControl::getControlInteraface setup the web interface
  * */
void BlindControl::getControlInteraface(){
    Serial.println("gui setup");
    Serial.println("gui setup");
    ESPUI.slider("Controller", handleRequest, COLOR_ALIZARIN, String(status));
    ESPUI.begin("Blinder Control");
    this->pinStart();
    ready = true;
}

/**
 * @brief BlindControl::handleButton handles button state change
 * */
void BlindControl::handleButton(){
    Serial.println(buttonUpStatus);
    Serial.println(buttonDownStatus);
    Serial.println(status);
    delay(250);
    if(ready){
        move();
        if(buttonUpStatus)
            setStatus(status-1);
        else if(buttonDownStatus)
            setStatus(status+1);
        else
            free = true;
    }
    
}
/**
 * @brief BlindControl::setStatus handles status change
 * */
void BlindControl::setStatus(int l_status){
    if(l_status>=0 && l_status<=100){
        Serial.println(status);
        int timetoSet = 0;
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
            pinToUse = 1;
        }
        else if(l_status>status){
            if(free)
                timetoSet = (downtime/100)*(l_status-status);
            else
                timetoSet += 500;
            if(pinToUse == upPin && time !=0){
                time = abs(time - timetoSet);
                stop();
                }
            else
                time += timetoSet;
            pinToUse = -1;
        }
        status = l_status;
        View::_cnf->setStatus(String(status));
        ESPUI.updateSlider(0, status);
    }

}