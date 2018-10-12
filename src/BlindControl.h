#ifndef BLINDCONTROL_H
#define BLINDCONTROL_H
#include "View.h"
#include <Update.h>

class BlindControl: public View{
private:
    static constexpr byte upPin = 25;
    static constexpr byte downPin = 26;
    static constexpr byte buttonUp = 19;
    static constexpr byte buttonDown = 21;
    static bool free;
    static int type;
    static int status;
    static int buttonUpStatus;
    static int buttonDownStatus;
    static bool ready;
    static AsyncWebServer server;
    static String lastKey;
    static unsigned long int emissionKey;
    static bool isHwButton;
    static bool readyConfigure;
    static unsigned long int uptime;
    static unsigned long int downtime;
    static unsigned long int time;
    static int pinToUse;
public:
    BlindControl(Configuration& cnf):View(cnf){}
    void move();
    static void hwButton();
    static void handleRequest(Control sender, int type);
    static void resetFunction(Control sender, int type);
    static void configblinder(Control sender, int type);
    static void doneconfig(Control sender, int type);
    static void setStatus(int status);
    static void pinStart();
    static bool isKeyValid(const String& key);
    static void getNewKey(AsyncWebServerRequest *request);
    static void badJson(AsyncWebServerRequest *request);
    static void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
    void setup();
    static void wifisetup();
    static void prepareDevice();
    static void getControlInteraface();
    void handleButton();
};

#endif