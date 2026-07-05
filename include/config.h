#pragma once

// --- Language configuration ---
#define LANGUAGE "en" // available: "pl" or "en"

// --- I2C pins ---
#define SDA_PIN D2
#define SCL_PIN D1

// --- Device I2C addresses ---
#define AHT20_ADDRESS 0x38
#define BMP280_ADDRESS 0x77
#define SSD1306_ADDRESS 0x3C

// --- Display configuration ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// --- WiFi configuration ---
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"

// --- MQTT configuration ---
#define ENABLE_MQTT true
#define MQTT_HOST "192.168.x.x"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "weather-station-esp8266-1"

#define TOPIC_TEMP  "home/station/temperature"
#define TOPIC_HUM   "home/station/humidity"
#define TOPIC_PRESS "home/station/pressure"

// --- Timing ---
#define PUBLISH_INTERVAL 2000UL