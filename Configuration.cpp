#include "Configuration.h"

String Configuration::newKey(){
  String toReturn = "";
  for (int i = 0 ; i < 30; i++) {
    byte randomValue = random(0, 37);
    char letter = randomValue + 'a';
    if (randomValue > 26)
      letter = (randomValue - 26) + '0';
  toReturn+=letter;
}

Configuration::Configuration(){
  pref.begin(name_mem, true);
  _ssid = pref.getString(ssid_key);
  _password = pref.getString(password_key);
  _api_key = pref.getString(api_key);
  _configured = pref.getBool(configured_key);
  pref.end();
  if(!_configured)
    setNewApiKey();
}

String Configuration::getWifiSSID() const{
  return _ssid;
}

String getWifiPassword() const{
  return _password;
}

String getApiKey() const{
  return _api_key;
}

bool isConfigured() const{
  return _configured;
}

void setWifiSSID(const String & ssid){
  _ssid = ssid;
  pref.begin(name_mem, false);
  pref.putString(ssid_key,_ssid);
  pref.end();
}

void setWifiPassword(const String & pwd){
  _password = pwd;
  pref.begin(name_mem, false);
  pref.putString(password_key,_password);
  pref.end();
}

void setNewApiKey(){
  _api_key = newKey();
  pref.begin(name_mem, false);
  pref.putString(api_key,_password);
  pref.end();
}

void setConfigured(bool cnf){
  _configured = cnf;
  pref.begin(name_mem, false);
  pref.putString(configured_key,_password);
  pref.end();
}

void reset(){
  pref.begin(name_mem, false);
  pref.clear();
  pref.end();
}
