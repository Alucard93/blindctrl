#ifndef WEBREQUESTSHANDLER_H
#define WEBREQUESTSHANDLER_H
#include <WebServer.h>
#include "Configuration.h"

class WebRequestHandler {
private:
  Configuration conf;
public:
  WebRequestHandler();
  void SetUp();
  void handle();
};

#endif
