#pragma once
#include "sensors.h"
#include <ESP8266WiFi.h>

extern IPAddress g_deviceIP;

void networkInit();
void networkEnsureConnected();
void networkLoop();
void networkPublish(const SensorReadings& r);