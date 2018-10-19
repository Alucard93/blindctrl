#ifndef SETUPSHUTTER_H
#define SETUPSHUTTER_H

#include "PinControl.h"
#include "View.h"

class SetupShutter: public PinControl, public View{
private:
    static bool readyConfigure;

public:
    SetupShutter(Configuration& cnf):View(cnf){}
    void setup();
    static void readyConf(Control sender, int type);
    static void saveConf(Control sender, int type);
    static void getInterface();
    void handleButton();
};

#endif