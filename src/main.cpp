#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "sensors.h"
#include "display_handler.h"
#include "network_handler.h"
#include "language.h"
#include "helpers.h"

unsigned long lastRead = 0;
SensorReadings lastPublished;
bool hasPublished = false;

bool publishedValuesChanged(const SensorReadings& a, const SensorReadings& b) {
  return quantize(a.temperature) != quantize(b.temperature) ||
         quantize(a.humidity)    != quantize(b.humidity)    ||
         quantize(a.pressure)    != quantize(b.pressure);
}

String getIpAsString() {
  if (g_deviceIP.isSet()) {
    return g_deviceIP.toString();
  }

  return "N/A";
}

void setup() {
  Serial.begin(74880);
  delay(500);

  Wire.begin(SDA_PIN, SCL_PIN);
  
  setLanguage(languageFromCode(LANGUAGE));

  displayInit();
  displayShowMessage(t(Str::INITIALIZING));

  sensorsInit();

  if (ENABLE_MQTT) {
    networkInit();
  }

  delay(1000);
}

void loop() {
  if (ENABLE_MQTT) {
    networkEnsureConnected();
    networkLoop();
  }

  if (millis() - lastRead > PUBLISH_INTERVAL) {
    lastRead = millis();

    SensorReadings r = sensorsRead();

    Serial.printf("AHT20: %.1f C, %.1f%% | BMP280: %.1f C, %.1f hPa\n",
                  r.temperature, r.humidity, r.auxTemperature, r.pressure);

    if (ENABLE_MQTT && r.valid && (!hasPublished || publishedValuesChanged(r, lastPublished))) {
      networkPublish(r);
      lastPublished = r;
      hasPublished = true;
    }

    String ip = getIpAsString();
    displayShowReadings(r, ip.c_str());
  }
}