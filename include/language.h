#pragma once
#include <Arduino.h>

enum class Lang {
  PL,
  EN
};

enum class Str {
  INITIALIZING,
  HUMIDITY,
  PRESSURE,
  COUNT
};

Lang languageFromCode(const char* code);
void setLanguage(Lang lang);
Lang getLanguage();
const char* t(Str id);