#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>
#include "sensors.h"
#include "config.h"

static Adafruit_AHTX0 aht;
static Adafruit_BMP280 bmp;
static bool ahtOk = false;
static bool bmpOk = false;

bool sensorsInit() {
  ahtOk = aht.begin(&Wire, 0, AHT20_ADDRESS);

  if (!ahtOk) {
    Serial.println("Didn't find AHT20 sensor!");
  }

  bmpOk = bmp.begin(BMP280_ADDRESS);

  if (!bmpOk) {
    Serial.println("Didn't find BMP280 sensor!");
  }

  return ahtOk && bmpOk;
}

SensorReadings sensorsRead() {
  SensorReadings r;
  r.valid = ahtOk && bmpOk;

  if (!r.valid) {
    r.temperature = 0.0f;
    r.auxTemperature = 0.0f;
    r.humidity = 0.0f;
    r.pressure = 0.0f;
    return r;
  }

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  r.temperature = temp.temperature;
  r.auxTemperature = bmp.readTemperature();
  r.humidity = humidity.relative_humidity;
  r.pressure = bmp.readPressure() / 100.0F; // convert Pa to hPa

  return r;
}