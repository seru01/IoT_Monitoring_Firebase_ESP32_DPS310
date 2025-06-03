#pragma once
#include <Arduino.h>
#include <WiFi.h>

class WiFi_Handler
{
private:
    bool sta_connected;
    bool ap_connected;

public:
    WiFi_Handler();
    ~WiFi_Handler();

    bool connectSTA();
    bool connectAP();

    bool isSTAConnected();
    bool isAPStarted();

    void printWiFiStatus();
};
