#ifndef SetupBlind_H
#define SetupBlind_H

#include "PinControl.h"
#include "View.h"

class SetupBlind: public PinControl, public View{
private:
    static bool readyConfigure;

public:
    SetupBlind(Configuration& cnf):View(cnf){}
    void setup();
    static void readyConf(Control sender, int type);
    static void saveConf(Control sender, int type);
    static void getInterface();
    void handleButton();
};

#endif