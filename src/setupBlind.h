#ifndef SETUPBLIND_H
#define SETUPBLIND_H

#include "Blind.h"

class setupBlind: public Blind{
private:
    static bool readyConfigure;

public:
    setupBlind(Configuration& cnf):Blind(cnf){}
    void setup();
    static void readyConf(Control sender, int type);
    static void saveConf(Control sender, int type);
    static void getInterface();
    void handleButton();
};

#endif