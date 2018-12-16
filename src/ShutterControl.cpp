#include "ShutterControl.h"

int ShutterControl::status = 0;
long int ShutterControl::time=0;
int ShutterControl::pinToUse=0;
bool PinControl::free=true;
double ShutterControl::unitDown;
double ShutterControl::unitUp;
Scheduler ShutterControl::ts;
Task* ShutterControl::toStop = nullptr;

/**
 * @brief ShutterControl::handleRequest handles the request from the slider
 * */
void ShutterControl::handleRequest(Control sender, int type){
    int requested_status = atoi(sender.value.c_str());
    if(free)
        setStatus(requested_status);
}

void ShutterControl::resetCalibration(Control sender, int type){
    View::_cnf->setStage(2);
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
    //ts.init();
}
 /**
  * @brief ShutterControl::getControlInteraface setup the web interface
  * */
void ShutterControl::getControlInteraface(){
    ESPUI.slider("Controller", handleRequest, COLOR_ALIZARIN, String(status));
    ESPUI.button("Calibration", resetCalibration, COLOR_EMERALD);
    ESPUI.begin("Shutter Control");
    this->pinStart();
    ready = true;
}

/**
 * @brief ShutterControl::handleButton handles button state change
 * */
void ShutterControl::handleButton(){
    long int lastrequ = millis() - time;
    if(ready){
        //move();
        if(buttonUpStatus){
            if(double(lastrequ)/unitUp >= 1 )
                setStatus(status-1);
        }
        else if(buttonDownStatus){
            if(double(lastrequ)/unitUp >= 1 )
            setStatus(status+1);
        }else{
            if(!free){
                stop();
                free = true;
            }
        }
    }
    ts.execute();
}
/**
 * @brief ShutterControl::setStatus handles status change
 * */
void ShutterControl::setStatus(int l_status){
    if(l_status>=0 && l_status<=100){
        if(toStop){
            if (toStop->isEnabled()){
                toStop->disable();
                delete toStop;
                toStop = nullptr;
            }
            if(!PinControl::upPin)
                status -= (millis() - time)/unitUp;
            if(!PinControl::downPin)
                status += (millis() - time)/unitDown;
        }
        int timetoSet = 0;
        if((buttonUpStatus || buttonDownStatus) && free)
        {
            PinControl::stop();
            free = false ;
        }
        if(l_status<status){
            timetoSet = ceil(unitUp*(status-l_status));
            PinControl::setUpPin();
        }
        else if(l_status>status){
            timetoSet = ceil(unitDown*(l_status-status));
            PinControl::setDownPin();
        }
        Serial.println(timetoSet*TASK_MILLISECOND);
        if(free){
            toStop = new Task(TASK_ONCE, TASK_ONCE, &PinControl::stop, &ts,true);
            toStop->delay(timetoSet * TASK_MILLISECOND);
        }
        time = millis();
        status = l_status;
        View::_cnf->setStatus(String(status));
        ESPUI.updateSlider(0, status);
    }else{
        stop();
    }
}
