#include "UpdateHandler.h"

RemoteDebug* UpdateHandler::Debug = nullptr;

UpdateHandler::UpdateHandler(){
    Debug = new RemoteDebug();
    Debug->begin("ShutterController");
    Debug->setSerialEnabled(true);
    Debug->setResetCmdEnabled(true);

    ArduinoOTA
    .onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";
        
        PinControl::setBootPin(); // makes the device ready for update

            //Debug->println(PinControl::getStatus());
            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Debug->println("Start updating " + type);

        })
    .onEnd([]() {
        Debug->println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
        Debug->printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
        Debug->printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Debug->println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Debug->println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Debug->println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Debug->println("Receive Failed");
        else if (error == OTA_END_ERROR) Debug->println("End Failed");
    });
    
    ArduinoOTA.begin();
}


void UpdateHandler::handle(){
    ArduinoOTA.handle();
    Debug->handle();
}