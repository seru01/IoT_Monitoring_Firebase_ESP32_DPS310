#pragma once
#include <Arduino.h>
#include <Adafruit_DPS310.h>
#include <Wire.h>

class Dps310Sensor
{
private:
	Adafruit_DPS310 dps310;
	bool initialized = false;

public:
	Dps310Sensor();
	bool begin();
	float getTemperature();
	float getPressure();
};
