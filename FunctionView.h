#ifndef FUNCTIONVIEW_H
#define FUNCTIONVIEW_H

#include <ESPUI.h>
#include "View.h"
#include "WifiSetup.h"

class FunctionView: public View{
private:
  static void slider(Control sender, int type);
public:
  FunctionView(Configuration& cnf):View(cnf){}
  void setup();
  void handle();
};
#endif
