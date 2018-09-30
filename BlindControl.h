#ifndef BLINDCONTROL_H
#define BLINDCONTROL_H
#include "View.h"
#include <ESPUI.h>
class BlindControl: public View{
private:
    static constexpr int time = 21000;
    static constexpr int unit = time/100;
    static constexpr byte upPin = 2;
    static constexpr byte downPin = 2;
    static constexpr byte buttonUp = 26;
    static constexpr byte buttonDown = 21;
    static bool free;
    static int type;
    static int status;
    static int buttonUpStatus;
    static int buttonDownStatus;
    static bool ready;
public:
    BlindControl(Configuration& cnf):View(cnf){}
    static void blinderUp(int up);
    static void blinderUp();
    static void blinderDown(int down);
    static void blinderDown();
    static void handleRequest(Control sender, int type);
    void setup();
    void wifisetup();
    void getControlInteraface();
    static void handleButton();
};

#endif