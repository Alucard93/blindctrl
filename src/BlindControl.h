#ifndef BLINDCONTROL_H
#define BLINDCONTROL_H

#include "PinControl.h"
#include "View.h"

class BlindControl: public PinControl, public View{
private:
    static int status;
    static long int time;
    static int pinToUse;
public:
    BlindControl(Configuration& cnf):View(cnf){}
    void move();
    static void handleRequest(Control sender, int type);
    static void setStatus(int status);
    void setup();
    void getControlInteraface();
    void handleButton();
};

#endif