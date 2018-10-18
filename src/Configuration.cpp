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
  _status = pref.getString(status_key);
  _uptime = pref.getULong(uptime_key);
  _downtime = pref.getULong(downtime_key);
  _stage_config = pref.getInt(config_stage_key);
  pref.end();
  if(_stage_config==0)
    setNewApiKey();
}

void Configuration::status(){
  pref.begin(name_mem, true);
  Serial.println();
  Serial.println(pref.getString(ssid_key).c_str());
  Serial.println(pref.getString(password_key).c_str());
  Serial.println(pref.getString(api_key).c_str());
  Serial.println(pref.getString(status_key));
  Serial.println(pref.getULong(uptime_key));
  Serial.println(pref.getULong(downtime_key));
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

String Configuration::getStatus() const{
  return _status;
}

unsigned long int Configuration::getUpTime() const{
  return _uptime;
}

unsigned long int Configuration::getDownTime() const{
  return _downtime;
}

int Configuration::getStage() const{
  return _stage_config;
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

void Configuration::setStatus(const String & status){
  _status = status;
  pref.begin(name_mem, false);
  pref.putString(status_key, _status);
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

void Configuration::setUpTime(unsigned long int rtime){
  _uptime = rtime;
  pref.begin(name_mem, false);
  pref.putULong(uptime_key, _uptime);
  pref.end();

}

void Configuration::setDownTime(unsigned long int rtime){
  _downtime = rtime;
  pref.begin(name_mem, false);
  pref.putULong(downtime_key, _downtime);
  pref.end();

}

void Configuration::setStage(int stage){
  _stage_config = stage;
  pref.begin(name_mem, false);
  pref.putInt(config_stage_key, _stage_config);
  pref.end();
}

void Configuration::reset(){
  pref.begin(name_mem, false);
  pref.clear();
  pref.end();
}
