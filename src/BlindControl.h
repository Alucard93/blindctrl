#ifndef BLINDCONTROL_H
#define BLINDCONTROL_H
#include "Blind.h"

class BlindControl: public Blind{
private:
    static int status;
    static long int time;
    static int pinToUse;
public:
    BlindControl(Configuration& cnf):Blind(cnf){}
    void move();
    static void handleRequest(Control sender, int type);
    static void resetFunction(Control sender, int type);
    static void setStatus(int status);
    void setup();
    void getControlInteraface();
    void handleButton();
};

#endif