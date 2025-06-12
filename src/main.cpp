
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoHA.h>
#include <DHT.h>
#include <TickTwo.h>

/*
  To include with credentials. This is what you need to do:

  1. Create a file called "Secret.h" in the same folder.
  2. Place the following text in the file:

#define ssid         "your_ssid"                     // replace with your WiFi SSID
#define password     "your_password"                 // replace with your WiFi password
#define mqttBrokerIp IPAddress(your,mqtt,broker,ip)  // replace with your MQTT broker IP address
#define mqttUser     "your_mqtt_user"                // replace with your credentials
#define mqttPassword "your_mqtt_password"            // replace with your credentials

  3. Save.
*/
#include "Secret.h"

#define DHTPIN  4      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
HADevice   device;
HAMqtt     mqtt(client, device);

HASensorNumber temp("dht22Temp", HASensorNumber::PrecisionP1);  // "dht22Temp" is the unique ID of the sensor.
HASensorNumber humi("dht22Humi", HASensorNumber::PrecisionP1);  // "dht22Humi" is the unique ID of the sensor.

void    readData();
TickTwo tReadData(readData, 1000, 0, MILLIS);  // Read data every 1 seconds.

void readData() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    temp.setValue(t);  // Send temperature value to Home Assistant
    humi.setValue(h);  // Send humidity value to Home Assistant
    Serial.printf("Temp: %.1f °C, Humi: %.1f %%\n", t, h);
}

void setup() {
    Serial.begin(115200);

    byte mac[6];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    dht.begin();

    device.setName("My ESP32");          // Device name
    device.setSoftwareVersion("1.0.0");  // Device software version

    temp.setName("DHT22 Temp");       // Sensor name
    temp.setUnitOfMeasurement("°C");  // Sensor unit of measurement
    humi.setName("DHT22 Humi");       // Sensor name
    humi.setUnitOfMeasurement("%");   // Sensor unit of measurement

    mqtt.begin(mqttBrokerIp, mqttUser, mqttPassword);
    tReadData.start();
}

void loop() {
    mqtt.loop();
    tReadData.update();
}
