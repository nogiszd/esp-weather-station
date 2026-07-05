#pragma once

struct SensorReadings {
  float temperature;
  float auxTemperature; // BMP280 readout, which has its own temperature reading
  float humidity;
  float pressure;
  bool valid;
};

bool sensorsInit();
SensorReadings sensorsRead();