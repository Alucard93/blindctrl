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
  return toReturn;
}

Configuration::Configuration(){
  pref.begin(name_mem, true);
  _ssid = pref.getString(ssid_key);
  _password = pref.getString(password_key);
  _api_key = pref.getString(api_key);
  _configured = pref.getBool(configured_key);
  _fsDone = pref.getBool(fs_done_key);
  pref.end();
  if(!_configured)
    setNewApiKey();
}

void Configuration::status(){
  pref.begin(name_mem, true);
  Serial.println();
  Serial.println(pref.getString(ssid_key).c_str());
  Serial.println(pref.getString(password_key).c_str());
  Serial.println(pref.getString(api_key).c_str());
  Serial.println(pref.getBool(configured_key));
  Serial.println();
  pref.end();
}

String Configuration::getWifiSSID() const{
  return _ssid;
}

String Configuration::getWifiPassword() const{
  return _password;
}

String Configuration::getApiKey() const{
  return _api_key;
}

bool Configuration::isConfigured() const{
  return _configured;
}

bool Configuration::isFsDone() const{
  return _fsDone;
}

void Configuration::setWifiSSID(const String & ssid){
  _ssid = ssid;
  pref.begin(name_mem, false);
  pref.putString(ssid_key,_ssid);
  pref.end();
}

void Configuration::setWifiPassword(const String & pwd){
  _password = pwd;
  pref.begin(name_mem, false);
  pref.putString(password_key,_password);
  pref.end();
}

void Configuration::setNewApiKey(){
  Serial.println("newkey");
  _api_key = newKey();
  Serial.println(_api_key.c_str());
  pref.begin(name_mem, false);
  pref.putString(api_key,_api_key);
  pref.end();
}

void Configuration::setConfigured(bool cnf){
  _configured = cnf;
  pref.begin(name_mem, false);
  pref.putBool(configured_key,_configured);
  pref.end();
}

void Configuration::setFsDone(bool cnf){
  _fsDone = cnf;
  pref.begin(name_mem, false);
  pref.putBool(fs_done_key,_fsDone);
  pref.end();
}

void Configuration::reset(){
  pref.begin(name_mem, false);
  pref.clear();
  pref.end();
}
