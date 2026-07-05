#include "language.h"

static Lang currentLang = Lang::PL;

static const char PL_INITIALIZING[] PROGMEM = "Inicjalizacja...";
static const char PL_HUMIDITY[] PROGMEM = "Wilgotnosc";
static const char PL_PRESSURE[] PROGMEM = "Cisnienie";

static const char EN_INITIALIZING[] PROGMEM = "Initializing...";
static const char EN_HUMIDITY[] PROGMEM = "Humidity";
static const char EN_PRESSURE[] PROGMEM = "Pressure";

static const char* const PL_STRINGS[] PROGMEM = {
  PL_INITIALIZING, PL_HUMIDITY, PL_PRESSURE
};

static const char* const EN_STRINGS[] PROGMEM = {
  EN_INITIALIZING, EN_HUMIDITY, EN_PRESSURE
};

Lang languageFromCode(const char* code) {
  if (strcmp(code, "en") == 0) {
    return Lang::EN;
  }

  return Lang::PL;
}

void setLanguage(Lang lang) {
  currentLang = lang;
}

Lang getLanguage() {
  return currentLang;
}

const char* t(Str id) {
  static char buffer[64];

  const char* const* table = (currentLang == Lang::PL) ? PL_STRINGS : EN_STRINGS;
  const char* progmemPtr = (const char*)pgm_read_ptr(&table[(int)id]);

  strncpy_P(buffer, progmemPtr, sizeof(buffer) - 1);
  buffer[sizeof(buffer) - 1] = '\0';

  return buffer;
}