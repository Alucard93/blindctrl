#ifndef VIEW_H
#define VIEW_H
#include "Configuration.h"
#include "WifiSetup.h";
class View{
protected:
  static Configuration* _cnf;
public:
  View(Configuration& cnf){_cnf = (&cnf);}
  virtual ~View() = default;
  virtual void setup() = 0;
  virtual void handle() = 0;

};

#endif
