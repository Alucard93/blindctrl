#ifndef WEBREQUESTSHANDLER_H
#define WEBREQUESTSHANDLER_H
#include <WebServer.h>
#include "Configuration.h"
#include "FunctionView.h"
#include "SetUpView.h"
#include "View.h"
class WebRequestsHandler {
private:
  Configuration* conf;
  View* view;
public:
  WebRequestsHandler();
  void setup();
  void handle();
};

#endif
