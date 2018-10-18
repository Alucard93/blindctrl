#ifndef WEBREQUESTSHANDLER_H
#define WEBREQUESTSHANDLER_H
#include "Configuration.h"
#include "BlindControl.h"
#include "SetUpView.h"
#include "setupBlind.h"
#include "View.h"

class WebRequestsHandler {
private:
  Configuration* conf;
  static View* view;
public:
  WebRequestsHandler();
  void setup();
  static void handle();
};

#endif
