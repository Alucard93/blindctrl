#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <Preferences.h>

class Configuration {
private:
  static constexpr char* name_mem = "BLNDR_CNF";
  static constexpr char* ssid_key = "ssid";
  static constexpr char* password_key = "pwd";
  static constexpr char* api_key = "api";
  static constexpr char* configured_key = "cnf";
  String _ssid, _password, _api_key;
  bool _configured;
  Preferences pref;
  String newKey();

public:
  Configuration();
  ~Configuration();
  String getWifiSSID() const;
  String getWifiPassword() const;
  String getApiKey() const;
  bool isConfigured() const;
  void setWifiSSID(const String & ssid);
  void setWifiPassword(const String & pwd);
  void setNewApiKey();
  void setConfigured(bool cnf=false);
  void reset();
};
#endif
