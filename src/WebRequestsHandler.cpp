#include "WebRequestsHandler.h"

View* WebRequestsHandler::view;


WebRequestsHandler::WebRequestsHandler(){
  conf = new Configuration();
  switch(conf->getStage()){
    case 0: 
      view = new SetUpView(*conf);
      break;
  case 1:
  case 2:
      view = new setupBlind(*conf);
      break;
  case 3:
      view = new BlindControl(*conf);
      break;
  }
}
void WebRequestsHandler::setup(){
  view->setup();
}
void WebRequestsHandler::handle(){
  view->handleButton();
}