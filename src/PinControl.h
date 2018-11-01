#ifndef PINCONTROL_H
#define PINCONTROL_H

#include <Arduino.h>

class PinControl{
protected:
    static constexpr int upPin = 25;
    static constexpr int downPin = 26;
    static constexpr int buttonUp = 19;
    static constexpr int buttonDown = 21;
    static constexpr int bootpin = 0;
    static constexpr int stdelay=20;
    static int buttonUpStatus;
    static int buttonDownStatus;
    static int downtime;
    static int uptime;
    static bool free;
    int type;

public:
    static bool ready;
    static void hwButton();
    void pinStart();
    void prepareDevice();
    static void stop();
    static void setUpPin();
    static void setDownPin();
    static void setBootPin();
    static String getStatus();
    static void readyLed(bool led=false);
};

#endif
