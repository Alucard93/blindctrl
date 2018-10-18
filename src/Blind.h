#ifndef BLIND_H
#define BLIND_H

#include "View.h"

class Blind: public View{
protected:
    static constexpr byte upPin = 25;
    static constexpr byte downPin = 26;
    static constexpr byte buttonUp = 19;
    static constexpr byte buttonDown = 21;
    static constexpr int stdelay=500;
    static int buttonUpStatus;
    static int buttonDownStatus;
    static int downtime;
    static int uptime;
    static bool free;
    int type;
    bool ready;

public:
    Blind(Configuration& cnf):View(cnf){}
    static void hwButton();
    void pinStart();
    void wifisetup();
    void prepareDevice();
    static void stop();
};

#endif