#include <ArduinoOTA.h>
#ifndef UPDATEHANDLER_H
#define UPDATEHANDLER_H

class UpdateHandler{
public:
    UpdateHandler();
    static void handle();
};

#endif UPDATEHANDLER_H