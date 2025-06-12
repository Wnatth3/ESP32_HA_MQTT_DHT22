# ESP32 Home Assistant MQTT DHT22 Sensor

## Prerequisites:
--------------
- Hardware:
* ESP32 development board
* DHT22 (AM2302/AM2321) temperature & humidity sensor
* Appropriate wiring (DHT22 data pin to GPIO 4 by default)
- Software:
* Arduino IDE or PlatformIO
* ESP32 board support installed
* Required libraries:
    - ArduinoHA
    - DHT sensor library
    - TickTwo
    - WiFi (built-in)
* A Home Assistant instance with MQTT integration enabled
* MQTT broker accessible on your network

## Features:
---------
- Connects ESP32 to WiFi and MQTT broker
- Reads temperature and humidity from DHT22 sensor every second
- Publishes sensor data to Home Assistant via MQTT auto-discovery
- Customizable device and sensor names
- Serial output for debugging and monitoring sensor values
- Secure credentials management via external Secret.h file

