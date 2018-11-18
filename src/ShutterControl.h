#ifndef SHUTTERCONTROL_H
#define SHUTTERCONTROL_H


#include <math.h>
#include <ESPUI.h>
#include "PinControl.h"
#include "View.h"
#include "WebRequestsHandler.h"

class ShutterControl: public PinControl, public View{
private:
    static int status;
    static long int time;
    static int pinToUse;
    static constexpr int up = 1;
    static constexpr int down = -1;
    static double unitDown;
    static double unitUp;
    static Scheduler ts;
    static Task* toStop;
public:
    ShutterControl(Configuration& cnf):View(cnf){}
    void move();
    static void handleRequest(Control sender, int type);
    static void resetCalibration(Control sender, int type);
    static void setStatus(int status);
    void setup();
    void getControlInteraface();
    void handleButton();
};

#endif
