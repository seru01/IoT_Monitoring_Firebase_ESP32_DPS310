#include "Dps310Sensor.h"

#define SDA_PIN 16
#define SCL_PIN 17

Dps310Sensor::Dps310Sensor() {}

bool Dps310Sensor::begin()
{
	Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C with custom pins

	if (!dps310.begin_I2C()) // Use default I2C address and Wire instance
	{
		Serial.println("DPS310 not detected!");
		initialized = false;
		return false;
	}

	initialized = true;
	return true;
}

float Dps310Sensor::getTemperature()
{
	if (!initialized)
		return NAN;

	sensors_event_t tempEvent;
	if (dps310.getTemperatureSensor()->getEvent(&tempEvent))
	{
		return tempEvent.temperature;
	}
	else
	{
		Serial.println("Temperature read failed");
		return NAN;
	}
}

float Dps310Sensor::getPressure()
{
	if (!initialized)
		return NAN;

	sensors_event_t pressureEvent;
	if (dps310.getPressureSensor()->getEvent(&pressureEvent))
	{
		return pressureEvent.pressure;
	}
	else
	{
		#ifdef DPS310_DEBUG == 1
		Serial.println("Pressure read failed");
		return NAN;
		#endif
	}
}
