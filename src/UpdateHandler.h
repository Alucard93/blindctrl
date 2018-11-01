#ifndef UPDATEHANDLER_H
#define UPDATEHANDLER_H

#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include "PinControl.h"

class UpdateHandler{
public:
    UpdateHandler();
    void handle();
};

#endif
