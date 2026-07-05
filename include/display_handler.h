#pragma once
#include "sensors.h"

bool displayInit();
void displayShowMessage(const char* line1, const char* line2 = "");
void displayShowReadings(const SensorReadings& readings, const char* ip = "?");