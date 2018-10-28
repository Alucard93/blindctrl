#include "ShutterControl.h"

int ShutterControl::status = 0;
long int ShutterControl::time=0;
int ShutterControl::pinToUse=0;
bool PinControl::free=true;


/**
 * @brief ShutterControl::move checks that time is 0 
 * */
void ShutterControl::move(){
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


}

/**
 * @brief ShutterControl::handleRequest handles the request from the slider
 * */
void ShutterControl::handleRequest(Control sender, int type){
    int requested_status = atoi(sender.value.c_str());
    setStatus(requested_status);
}


/**
 * @brief ShutterControl::setup() prepare the device already configured
 * */
void ShutterControl::setup(){
    View::_cnf->reset();
    Serial.println("ShutterControl: setUp");
    uptime = View::_cnf->getUpTime();
    downtime = View::_cnf->getDownTime();
    getControlInteraface();
    PinControl::readyLed(true);
}
 
 /**
  * @brief ShutterControl::getControlInteraface setup the web interface
  * */
void ShutterControl::getControlInteraface(){
    ESPUI.slider("Controller", handleRequest, COLOR_ALIZARIN, String(status));
    ESPUI.begin("Shutter Control");
    this->pinStart();
    ready = true;
}

/**
 * @brief ShutterControl::handleButton handles button state change
 * */
void ShutterControl::handleButton(){
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
 * @brief ShutterControl::setStatus handles status change
 * */
void ShutterControl::setStatus(int l_status){
    if(l_status>=0 && l_status<=100){
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