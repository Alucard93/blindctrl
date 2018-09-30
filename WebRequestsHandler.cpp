#include "WebRequestsHandler.h"

WebRequestsHandler::WebRequestsHandler(){
  conf = new Configuration();
  conf->status();
  if(conf->isConfigured())
    view = new BlindControl(*conf);
  else
    view = new SetUpView(*conf);
}
void WebRequestsHandler::setup(){
  view->setup();
}
void WebRequestsHandler::handle(){
  BlindControl::handleButton();
}