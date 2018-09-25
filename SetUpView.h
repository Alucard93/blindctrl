#ifndef SETUPVIEW_H
#define SETUPVIEW_H
#include "View.h"

class SetUpView : public View{
public:
  static void selectWifi();
  static void insertPassword();
  static void getApi();
  static void error();
  static void reboot();
  void setup();
};

#endif
