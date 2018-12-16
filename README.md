# ShutterControl
Is a project for shutter automation and IoT intregration based on ESP32 and
2Relay module with a Hi-link psu.
The software uses a meshed network for all the IoT devices based on ESP32 and
uses MQTT protocol for messages and commands

## Getting Started
After flashing the firmware at the first boot it will create an access point without
password (it will be added in the future).
Navigate to esp32.local and it will ask for network credentials to connect to
your local network

## Usage

All the interaction in this stage will be executed by web interface, in the final
release all the interaction will be accepted only via MQTT.



## Built With
- PlatformIO
- Arduino
- ESPUI
- ESP Async WebServer
- ArduinoJson
- painlessMesh
- TaskScheduler
