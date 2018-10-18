#include "Blind.h"

int Blind::buttonUpStatus = 0;
int Blind::buttonDownStatus = 0;
int Blind::downtime = 0;
int Blind::uptime = 0;

void Blind::hwButton(){
    buttonDownStatus = digitalRead(buttonDown);
    buttonUpStatus = digitalRead(buttonUp);
}

void Blind::pinStart(){
    pinMode(upPin, OUTPUT);
    pinMode(downPin, OUTPUT);
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
    attachInterrupt(digitalPinToInterrupt(buttonUp),hwButton,RISING);
    attachInterrupt(digitalPinToInterrupt(buttonDown),hwButton,RISING);
    stop();
}

void Blind::wifisetup(){
    WifiSetup::connect(View::_cnf->getWifiSSID(),View::_cnf->getWifiPassword());
}

void Blind::prepareDevice(){
    Serial.println("preparing filesystem");
    ESPUI.prepareFileSystem();
}

void Blind::stop(){
    digitalWrite(upPin, HIGH);
    digitalWrite(downPin, HIGH);
}