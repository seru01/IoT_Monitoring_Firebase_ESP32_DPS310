#pragma once

// Configuration settings for the project
#define CONFIG_VERSION "1.0.0"
#define CONFIG_AUTHOR ""
#define CONFIG_DATE ""
#define CONFIG_HARDWARE_VERSION "1.0"
#define CONFIG_SOFTWARE_VERSION "1.0.0"

// PERIPHERAL CONFIGURATION
#define LED_PIN 18		  // GPIO pin for the LED


// General configuration settings
#define CONFIG_WIFI_TIMEOUT 60000	  // Timeout for WiFi connection in milliseconds
#define CONFIG_SERIAL_BAUDRATE 115200 // Serial communication baud rate
#define CONFIG_DEBUG_ENABLED true	  // Enable or disable debug messages
#define CONFIG_LOG_LEVEL 0			  // Log level: 0 = None, 1 = Error, 2 = Warning, 3 = Info, 4 = Debug
