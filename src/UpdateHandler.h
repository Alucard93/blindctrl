#ifndef UPDATEHANDLER_H
#define UPDATEHANDLER_H

#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include "PinControl.h"
#include <RemoteDebug.h>

class UpdateHandler{
public:
    static RemoteDebug* Debug;
    UpdateHandler();
    void handle();
};

#endif