#include "Mqtt_Handler.h"
#include "include/MqttConfig.h"
#include <ArduinoJson.h>
#include <Arduino.h>
#include <Config.h>

#define LED_PIN 18 // You can also move this to Config.h

MqttClient::MqttClient()
	: server(MQTT_BROKER_ADDRESS),
	  port(MQTT_BROKER_PORT),
	  user(MQTT_USERNAME),
	  password(MQTT_PASSWORD),
	  publishTopic(MQTT_TOPIC),
	  ledControlTopic(MQTT_LED_TOPIC),
	  qos(MQTT_QOS),
	  client(secureClient)
{
	secureClient.setInsecure();
	client.setServer(server, port);

	// Bind callback using lambda to allow access to 'this'
	client.setCallback([this](char *topic, byte *message, unsigned int length)
					   { this->callback(topic, message, length); });
}

void MqttClient::connect()
{
	if (WiFi.status() != WL_CONNECTED)
	{
		Serial.println("MQTT skipped: no WiFi connection.");
		return;
	}

	unsigned long startAttemptTime = millis();

	while (!client.connected() && (millis() - startAttemptTime < MQTT_TIMEOUT_MS))
	{
		Serial.println("Attempting to connect to MQTT...");

		if (client.connect(MQTT_CLIENT_ID, user, password))
		{
			Serial.println("✅ Connected to MQTT broker");
			client.subscribe(publishTopic, qos);	// For sensor data (if needed)
			client.subscribe(ledControlTopic, qos); // For LED control
			return;
		}
		else
		{
			Serial.printf("❌ MQTT connection failed, rc=%d\n", client.state());
			delay(1000);
		}
	}

	if (!client.connected())
	{
		Serial.println("❌ MQTT connection timeout. Continuing without MQTT.");
	}
}

void MqttClient::loop()
{
	if (!client.connected())
	{
		connect();
	}
	client.loop();
}

void MqttClient::publish(const char *message)
{
	if (!client.connected())
	{
		Serial.println("Cannot publish, MQTT not connected.");
		return;
	}

	if (client.publish(publishTopic, message, qos))
	{
		Serial.printf("📤 Published to topic: %s\n", publishTopic);
	}
	else
	{
		Serial.println("❌ Failed to publish message");
	}
}

void MqttClient::publishSensorData(float temperature, float pressure)
{
	JsonDocument doc;
	doc["temperature"] = temperature;
	doc["pressure"] = pressure;

	char payload[256];
	serializeJson(doc, payload);
	publish(payload);
}

void MqttClient::callback(char *topic, byte *message, unsigned int length)
{
	String topicStr(topic);
	String msg;

	for (unsigned int i = 0; i < length; i++)
	{
		msg += (char)message[i];
	}

	Serial.printf("📩 MQTT Message on [%s]: %s\n", topicStr.c_str(), msg.c_str());

	if (topicStr == ledControlTopic)
	{
		if (msg == "on")
		{
			digitalWrite(LED_PIN, HIGH);
			Serial.println("💡 LED turned ON");
		}
		else if (msg == "off")
		{
			digitalWrite(LED_PIN, LOW);
			Serial.println("💡 LED turned OFF");
		}
		else
		{
			Serial.println("⚠️ Unknown LED command");
		}
	}
}
