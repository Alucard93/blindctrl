#include "BlindControl.h"

bool BlindControl::free = true;
int BlindControl::status = 0;
int BlindControl::buttonUpStatus = 0;
int BlindControl::buttonDownStatus = 0;
bool BlindControl::ready = false;
AsyncWebServer BlindControl::server(80);
String BlindControl::lastKey="";
unsigned long int BlindControl::emissionKey;
bool BlindControl::isHwButton=false;
bool BlindControl::readyConfigure = false;
unsigned long int BlindControl::uptime;
unsigned long int BlindControl::downtime;
unsigned long int BlindControl::time=0;
int BlindControl::pinToUse=0;

void BlindControl::hwButton(){
    buttonDownStatus = digitalRead(buttonDown);
    buttonUpStatus = digitalRead(buttonUp);
}

void BlindControl::move(){
    unsigned long int pretime = millis();
    if(!pinToUse)
    {
        if(!time)
            digitalWrite(pinToUse, LOW);
        else    
            digitalWrite(pinToUse, HIGH);
    }
    unsigned long int aferTime = millis();
    if(pretime - aferTime < 0)
        time = 0;
    else
        time -= pretime - aferTime;


}

void BlindControl::handleRequest(Control sender, int type){
    int requested_status = atoi(sender.value.c_str());
    setStatus(requested_status);
}

void BlindControl::resetFunction(Control sender, int type){
    View::_cnf->reset();
    ESP.restart();
}

void BlindControl::configblinder(Control sender, int type){
    readyConfigure = true;
    emissionKey = millis();
}

void BlindControl::doneconfig(Control sender, int type){
    View::_cnf->setDownTime(downtime);
    View::_cnf->setUpTime(uptime);
    View::_cnf->setFsDone();
    ESP.restart();
}

void BlindControl::prepareDevice(){
    Serial.println("preparing filesystem");
    ESPUI.prepareFileSystem();
    ESPUI.label("",COLOR_ALIZARIN,"before Start configuration make sure that the blinder is all the way up for calibration");
    ESPUI.label("",COLOR_ALIZARIN,"To complete the calibration make the blinder go all the way down and then make it go all the way up");
    ESPUI.button("Start",configblinder,COLOR_CARROT,"Start configuration");
    ESPUI.button("ready to go up",configblinder,COLOR_CARROT,"going up");
    ESPUI.button("Completed",doneconfig,COLOR_CARROT,"save and reboot");
    ESPUI.begin("First configuration");
    pinStart();
}

void BlindControl::setup(){
    Serial.println("setUp");
    if(View::_cnf->isConfigured())
        wifisetup();
    if(View::_cnf->getStatus() == "")
        status = 0;
    else
        status = atoi(View::_cnf->getStatus().c_str());

    uptime = View::_cnf->getUpTime();
    downtime = View::_cnf->getDownTime();

    if(!View::_cnf->isFsDone())
        prepareDevice();
    else{
        getControlInteraface();
    }
    server.onFileUpload(handleUpload);
    ready = true;
}

void BlindControl::getControlInteraface(){
    Serial.println("gui setup");
    Serial.println("gui setup");
    ESPUI.slider("Controller", handleRequest, COLOR_ALIZARIN, String(status));
    ESPUI.button("",resetFunction, COLOR_ALIZARIN, "reset button");
    ESPUI.begin("Blinder Control");
    AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/"+View::_cnf->getApiKey(), [](AsyncWebServerRequest *request, JsonVariant &json) {
        JsonObject& jsonObj = json.as<JsonObject>();
        if(jsonObj.containsKey("comKey"))
        {
            if(isKeyValid(jsonObj.get<String>("comKey")) && jsonObj.containsKey("newValue"))
                setStatus(jsonObj.get<unsigned int>("newValue"));
            else if (!isKeyValid(jsonObj.get<String>("comKey")))
                getNewKey(request);
            else
                badJson(request);
        }

    });
    server.addHandler(handler);
    pinStart();
}

void BlindControl::pinStart(){
    pinMode(upPin, OUTPUT);
    pinMode(downPin, OUTPUT);
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
    attachInterrupt(digitalPinToInterrupt(buttonUp),hwButton,RISING);
    attachInterrupt(digitalPinToInterrupt(buttonDown),hwButton,RISING);
    digitalWrite(upPin,HIGH);
    digitalWrite(downPin,HIGH);digitalWrite(upPin,HIGH);
    
}

void BlindControl::wifisetup(){
    //Serial.println("test connection");
    //WifiSetup::connect(View::_cnf->getWifiSSID(),View::_cnf->getWifiPassword());
    WifiSetup::wifiAsAP("test");
}

void BlindControl::handleButton(){
    delay(500);
    if(ready){
        move();        
        if(View::_cnf->isFsDone()){
            if(buttonUpStatus){
                setStatus(status-1);
                ESPUI.updateSlider(0, status);
            }
            if(buttonDownStatus){
                setStatus(status+1);
                ESPUI.updateSlider(0, status);
            }

        }else{
            if(buttonUpStatus){
                digitalWrite(upPin, LOW);
                digitalWrite(downPin, HIGH);
                if(readyConfigure && free){
                    uptime = millis();//savetime
                    free = false;
                }
            } else if (buttonDownStatus){
                digitalWrite(downPin, LOW);
                digitalWrite(upPin, HIGH);
                if(readyConfigure && free){
                    downtime = millis();//savetime
                    free = false;
                }
            }else{
                free = true;
                digitalWrite(upPin, HIGH);
                digitalWrite(downPin, HIGH);
                if(readyConfigure){
                    uptime = millis()-uptime;
                    downtime = millis() - downtime;
                }
            }
        }
    }
    
}

void BlindControl::setStatus(int l_status){
    if((buttonUpStatus || buttonDownStatus) && free)
    {
        time = 0 ;
        pinToUse = 0 ;
        free = false ;
    }else{
        free = true ;
    }
    if(l_status<status){
        time += (uptime/100)*(status-l_status);
        pinToUse = upPin;
    }
    else if(l_status>status){
        time += (downtime/100)*(l_status-status);
        pinToUse = downPin;
    }

}

bool BlindControl::isKeyValid(const String& key){
    return (key == lastKey) && ((millis()-emissionKey)<60000);
}

void BlindControl::getNewKey(AsyncWebServerRequest *request){
    emissionKey = millis();
    String toReturn = "";
    for (int i = 0 ; i < 30; i++) {
        byte randomValue = random(0, 37);
        char letter = randomValue + 'a';
        if (randomValue > 26)
            letter = (randomValue - 26) + '0';
        toReturn+=letter;
    }
    //emissionKey = now();
    request->send(200,"application/json","{newKey:"+toReturn+"}");
}

void BlindControl::badJson(AsyncWebServerRequest *request){
    //badjson
    request->send(400,"text/html","nope");
}

void BlindControl::handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if(!index){
        Serial.printf("UploadStart: %s\n", filename.c_str());
    }
    for(size_t i=0; i<len; i++){
        Serial.write(data[i]);
    }
    if(final){
        Serial.printf("UploadEnd: %s, %u B\n", filename.c_str(), index+len);
    }
}