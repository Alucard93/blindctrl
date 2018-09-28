#include "WebRequestsHandler.h"

WebRequestsHandler::WebRequestsHandler(){
  conf = new Configuration();
  conf->status();
  if(conf->isConfigured())
    view = new FunctionView(*conf);
  else
    view = new SetUpView(*conf);
}
void WebRequestsHandler::setup(){
  view->setup();
}
void WebRequestsHandler::handle(){
  view->handle();
}
