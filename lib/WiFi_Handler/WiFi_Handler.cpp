#include "WiFi_Handler.h"
#include "include/WiFiConfig.h"

WiFi_Handler::WiFi_Handler() : sta_connected(false), ap_connected(false) {}

WiFi_Handler::~WiFi_Handler() {}

bool WiFi_Handler::connectSTA()
{
	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_STA_SSID, WIFI_STA_PASSWORD);
#ifdef WIFI_DEBUGG == 0
	printf("[%s:%i]"
		   "Connecting to WiFi SSID: %s\n",
		   __FILENAME__, __LINE__, WIFI_STA_SSID);
#endif
	unsigned long startAttemptTime = millis();

	while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
	{
		delay(500);
		Serial.print(".");
	}
	sta_connected = WiFi.status() == WL_CONNECTED;
	printWiFiStatus();
	return sta_connected;
}

bool WiFi_Handler::connectAP()
{
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(WIFI_AP_IP, WIFI_AP_GATEWAY, WIFI_AP_SUBNET);
	ap_connected = WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);
	printWiFiStatus();
	return ap_connected;
}

bool WiFi_Handler::isSTAConnected()
{
	return sta_connected;
}

bool WiFi_Handler::isAPStarted()
{
	return ap_connected;
}

void WiFi_Handler::printWiFiStatus()
{
	if (sta_connected)
	{
#ifdef WIFI_DEBUGG == 0
		printf("[%s:%i]"
			   "SSID: %s\n",
			   __FILENAME__, __LINE__, WIFI_STA_SSID);
		printf("[%s:%i] IP Address: %s\n", __FILENAME__, __LINE__, WiFi.localIP().toString().c_str());
#endif
	}
	else if (ap_connected)
	{
#ifdef WIFI_DEBUGG == 0
		printf("[%s:%i]"
			   "AP started successfully. \n",
			   __FILENAME__, __LINE__);
		printf("[%s:%i]"
			   "AP SSID: \n",
			   __FILENAME__, __LINE__, WiFi.softAPSSID().c_str());

#endif
	}
	else
	{
#if WIFI_DEBUGG == 0
		printf("[%s:%i]"
			   "Failed to connect to WiFi.\n",
			   __FILENAME__, __LINE__);
#endif
	}
}
