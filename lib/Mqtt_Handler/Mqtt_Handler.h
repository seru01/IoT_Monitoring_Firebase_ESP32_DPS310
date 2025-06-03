#pragma once

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

class MqttClient
{
private:
	const char *server;
	const int port;
	const char *user;
	const char *password;
	const char *publishTopic;
	const char *ledControlTopic;
	const int qos;

	WiFiClientSecure secureClient;
	PubSubClient client;

	void callback(char *topic, byte *message, unsigned int length);

public:
	MqttClient();

	void connect();
	void loop();
	void publish(const char *message);
	void publishSensorData(float temperature, float pressure);
};
