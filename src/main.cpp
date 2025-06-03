#include <Arduino.h>
#include <Config.h>
#include <WiFi_Handler.h>
#include <Mqtt_Handler.h>
#include <Dps310Sensor.h>

WiFi_Handler wifi;
MqttClient mqtt;
Dps310Sensor dps;

unsigned long lastPublish = 0;
const unsigned long publishInterval = 5000; // every 5 second

void setup()
{
	Serial.begin(CONFIG_SERIAL_BAUDRATE);
	// LED
	pinMode(LED_PIN, OUTPUT);

	// WIFI
	if (!wifi.connectSTA())
	{
		wifi.connectAP();
	}

	// Sensor
	if (!dps.begin())
	{
		Serial.println("Failed to initialize DPS310 sensor.");
	}

	// MQTT
	mqtt.connect();
}

void loop()
{
	mqtt.loop(); // Keep MQTT alive

	// DPS310 Sensor publish data
	if (millis() - lastPublish >= publishInterval)
	{
		lastPublish = millis();

		float temp = dps.getTemperature();
		float pressure = dps.getPressure();

		if (!isnan(temp) && !isnan(pressure))
		{
			mqtt.publishSensorData(temp, pressure);
		}
	}
}
