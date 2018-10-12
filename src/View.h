
#include "Configuration.h"
#include "WifiSetup.h"
#include <ESPUI.h>
#include <time.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>

#ifndef VIEW_H
#define VIEW_H

class View{
protected:
  static Configuration* _cnf;
public:
  View(Configuration& cnf){_cnf = (&cnf);}
  virtual ~View() = default;
  virtual void handleButton() =0;
  virtual void setup() = 0;
};

#endif
