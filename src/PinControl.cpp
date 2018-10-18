#include "PinControl.h"

int PinControl::buttonUpStatus = 0;
int PinControl::buttonDownStatus = 0;
int PinControl::downtime = 0;
int PinControl::uptime = 0;

void PinControl::hwButton(){
    buttonDownStatus = digitalRead(buttonDown);
    buttonUpStatus = digitalRead(buttonUp);
}

void PinControl::pinStart(){
    pinMode(upPin, OUTPUT);
    pinMode(downPin, OUTPUT);
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
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