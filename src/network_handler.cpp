#include "network_handler.h"
#include "config.h"
#include "helpers.h"
#include <ESP8266WiFi.h>
#include <MQTTClient.h>

IPAddress g_deviceIP;

static WiFiClient espClient;
static MQTTClient mqttClient(256);

static void connectWiFi() {
  Serial.print("\nConnecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print(" OK");
  Serial.println();

  g_deviceIP = WiFi.localIP();

  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(g_deviceIP);
}

static void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT server...");

    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      Serial.println(" OK\n");
    } else {
      Serial.printf(" failed. Trying again in 2 seconds...\n");
      delay(2000);
    }
  }
}

void networkInit() {
  connectWiFi();
  mqttClient.begin(MQTT_HOST, MQTT_PORT, espClient);
  connectMQTT();
}

void networkEnsureConnected() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (!mqttClient.connected()) connectMQTT();
}

void networkLoop() {
  mqttClient.loop();
}

void networkPublish(const SensorReadings& r) {
  if (!r.valid) return;

  char buf[16];

  dtostrf(r.temperature, 4, 1, buf);
  mqttClient.publish(TOPIC_TEMP, buf);

  dtostrf(r.humidity, 4, 1, buf);
  mqttClient.publish(TOPIC_HUM, buf);

  dtostrf(r.pressure, 6, 1, buf);
  mqttClient.publish(TOPIC_PRESS, buf);
}