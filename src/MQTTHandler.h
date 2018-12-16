#include <AsyncMqttClient.h>

#ifndef MQTTHandler
#define MQTTHandler

class MQTTHandler {
private:
    AsyncMqttClient cli;

public:
    MQTTHandler(int port=1883);
    
}

#endif
