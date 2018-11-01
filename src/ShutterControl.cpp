#include "ShutterControl.h"

int ShutterControl::status = 0;
long int ShutterControl::time=0;
int ShutterControl::pinToUse=0;
bool PinControl::free=true;
double ShutterControl::unitDown;
double ShutterControl::unitUp;


/**
 * @brief ShutterControl::move checks that time is 0
 * */
void ShutterControl::move(){
    if(time>0){
        Serial.println(time);
        if(pinToUse == 1){
            PinControl::setUpPin();
            delay(ceil(unitUp));
            time -= ceil(unitUp);
        }
        if(pinToUse == -1){
            PinControl::setDownPin();
            delay(ceil(unitDown));
            time -= ceil(unitDown);
        }
    }else{
        time = 0;
        stop();
    }
}

/**
 * @brief ShutterControl::handleRequest handles the request from the slider
 * */
void ShutterControl::handleRequest(Control sender, int type){
    int requested_status = atoi(sender.value.c_str());
    if(free)
        setStatus(requested_status);
}


/**
 * @brief ShutterControl::setup() prepare the device already configured
 * */
void ShutterControl::setup(){
    Serial.println("ShutterControl: setUp");
    status = atoi(View::_cnf->getStatus().c_str());
    uptime = View::_cnf->getUpTime();
    downtime = View::_cnf->getDownTime();
    Serial.println(uptime);
    Serial.println(downtime);
    unitUp = double(uptime)/100;
    unitDown = double(downtime)/100;
    Serial.println(unitUp);
    Serial.println(unitDown);
    getControlInteraface();
    PinControl::readyLed(true);
    ESPUI.updateSlider(0, status);
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
    delay(stdelay);
    if(ready){
        move();
        if(buttonUpStatus)
            setStatus(status-1);
        else if(buttonDownStatus)
            setStatus(status+1);
        else
            free = true;
    }
    ESPUI.updateSlider(0, status);
}
/**
 * @brief ShutterControl::setStatus handles status change
 * */
void ShutterControl::setStatus(int l_status){
    if(l_status>=0 && l_status<=100){
        int timetoSet = 0;
        if((buttonUpStatus || buttonDownStatus) && free)
        {
            if(time !=0){
                if(pinToUse == 1 )
                    status += time/unitUp;
                if(pinToUse == -1)
                    status -= time/unitDown;
            }
            time = 0 ;
            stop();
            free = false ;
        }
        if(l_status<status){
            timetoSet = ceil(unitUp*(status-l_status));
            pinToUse = 1;
        }
        else if(l_status>status){
            timetoSet = ceil(unitUp*(l_status-status));
            pinToUse = -1;
        }
        time +=timetoSet;
        status = l_status;
        View::_cnf->setStatus(String(status));
    }

}
