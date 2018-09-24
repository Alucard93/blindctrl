#include "Configs.h"

Preferences Configs::pref;

void Configs::begin() {
  pref.begin(name_mem, false);
  configured = pref.getBool(configured_key);
  ssid = const_cast<char*>(pref.getString(ssid_key).c_str());
  pwd = const_cast<char*>(pref.getString(password_key).c_str());
  rnd_key = const_cast<char*>(pref.getString(api_key).c_str());
}

void Configs::end() {
  pref.putString(ssid_key, ssid);
  pref.putString(password_key, pwd);
  pref.putString(api_key, rnd_key);
  pref.putBool(configured_key, configured);
  pref.end();
}

bool Configs::isConfigured()  {
  return configured;
}

char* Configs::getSSID()  {
  return ssid;
}

char* Configs::getPassword()  {
  return pwd;
}

char* Configs::getApiKey()  {
  return rnd_key;
}

void Configs::setSSID(const String& fssid) {
  ssid = const_cast<char*>(fssid.c_str());
  pref.putString(ssid_key, ssid);
}

void Configs::setPassword(const String& fpwd) {
  pwd = const_cast<char*>(fpwd.c_str());
  pref.putString(password_key, pwd);
}

void Configs::setConfigured(){
  pref.putBool(configured_key, true);
}

void Configs::setKey(){
  rnd_key = const_cast<char*>(newKey().c_str());
  pref.putString(api_key,rnd_key);
}

String Configs::newKey(){
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

void Configs::reset(){
  pref.clear();
}
