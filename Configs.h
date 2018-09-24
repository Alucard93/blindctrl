#include <Preferences.h>

#ifndef CONFIGS_H
#define CONFIGS_H
class Configs {
public:
    static constexpr char* name_mem = "BLNDR_CNF";
    static constexpr char* ssid_key = "ssid";
    static constexpr char* password_key = "pwd";
    static constexpr char* api_key = "api";
    static constexpr char* configured_key = "cnf";
    static Preferences pref;
    bool configured;
    char * ssid;
    char * pwd;
    char * rnd_key;
    static String newKey();
    void begin();
    void end();
    bool isConfigured();
    char * getSSID();
    char * getPassword();
    char * getApiKey();
    void setKey();
    void reset();
    void setSSID(const String& fssid);
    void setPassword(const String& fpwd);
    void setConfigured();
};

#endif
