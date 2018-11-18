#ifndef SETUPSHUTTER_H
#define SETUPSHUTTER_H

#include <ESPUI.h>
#include "PinControl.h"
#include "View.h"

class SetupShutter: public PinControl, public View{
private:
    static int configureUp;
    static int configureDown;

public:
    SetupShutter(Configuration& cnf):View(cnf){}
    void setup();
    static void upConf(Control sender, int type);
    static void downConf(Control sender, int type);
    static void saveConf(Control sender, int type);
    static void getInterface();
    void handleButton();
};

#endif
