#include "PinControl.h"

int PinControl::buttonUpStatus = 0;
int PinControl::buttonDownStatus = 0;
int PinControl::downtime = 0;
int PinControl::uptime = 0;
bool PinControl::ready = false;
void PinControl::hwButton(){
    if(ready){
        buttonDownStatus = digitalRead(buttonDown);
        buttonUpStatus = digitalRead(buttonUp);
    }
}

void PinControl::pinStart(){
    pinMode(upPin, OUTPUT);
    pinMode(downPin, OUTPUT);
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
    pinMode(2,OUTPUT);
    attachInterrupt(digitalPinToInterrupt(buttonUp),hwButton,RISING);
    attachInterrupt(digitalPinToInterrupt(buttonDown),hwButton,RISING);
    stop();
}

void PinControl::prepareDevice(){
    Serial.println("preparing filesystem");
    ESPUI.prepareFileSystem();
}

void PinControl::stop(){
    digitalWrite(upPin, HIGH);
    digitalWrite(downPin, HIGH);
}

void PinControl::setUpPin(){
    digitalWrite(upPin, LOW);
    digitalWrite(downPin, HIGH);
}

void PinControl::setDownPin(){
    digitalWrite(downPin, LOW);
    digitalWrite(upPin, HIGH);
}

void PinControl::setBootPin(){
    stop();
    digitalWrite(2,LOW);
    pinMode(bootpin, OUTPUT);
    digitalWrite(bootpin, LOW);
    delay(100);
    digitalWrite(bootpin, HIGH);
}

void PinControl::readyLed(bool led){
    digitalWrite(2,led);
}

String PinControl::getStatus(){
    String toReturn="Pulsante giu"+'\n';
    toReturn += digitalRead(buttonDown)+'\n';
    toReturn += "Pulsante Su"+'\n';
    toReturn += digitalRead(buttonUp)+'\n';
    toReturn += "relay giu"+'\n';
    toReturn += digitalRead(downPin)+'\n';
    toReturn += "relay su"+'\n';
    toReturn += digitalRead(upPin)+'\n';
    toReturn += "boot"+'\n';
    toReturn += digitalRead(bootpin)+'\n';
    
}