#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "display_handler.h"
#include "config.h"
#include "language.h"

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool displayInit() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS)) {
    Serial.println("SSD1306 allocation failed!");
    return false;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  return true;
}

void displayShowMessage(const char* line1, const char* line2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(line1);

  if (line2[0] != '\0') {
    display.println(line2);
  }
  display.display();
}

void displayShowReadings(const SensorReadings& r, const char* ip) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.printf("IP: %s\n", ip);
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 16);
  display.printf("%.1f ", r.temperature);

  int16_t x = display.getCursorX();
  int16_t y = display.getCursorY();
  display.drawCircle(x + 3, y + 2, 2, SSD1306_WHITE);

  display.setCursor(x + 8, y);
  display.print("C\n");

  display.setTextSize(1);
  display.setCursor(0, 36);
  display.printf("%s: %.1f%%\n", t(Str::HUMIDITY), r.humidity);
  display.setCursor(0, 48);
  display.printf("%s: %.1f hPa", t(Str::PRESSURE), r.pressure);

  display.display();
}