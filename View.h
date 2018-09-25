#ifndef VIEW_H
#define VIEW_H
#include "Configuration.h"
#include <WebServer.h>

class View{
protected:
  Configuration& _cnf
  WebServer& _server
public:
  View(Configuration& cnf, WebServer& server):_cnf(cnf),_server(server){}
  virtual ~View() = default;
  virtual void setup() = 0;
  WebServer& getServer(){
    return _server;
  }

};

#endif
