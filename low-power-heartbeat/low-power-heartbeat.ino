#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Xiaomi_Hello";
const char* password = "12345678";
const int sleepTimeS = 3600;
const int led = 13;
const char* host = "http://portal.xiandusi.com:1337/example/classes/LowPowerHeartbeat";

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  HTTPClient http;
  http.begin(host);
  digitalWrite(led, 1);
  http.addHeader("X-Parse-Application-Id", "123456");
  http.addHeader("X-Parse-REST-API-KEY", "123456");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST("{\"sn\": \"1\"}");
  http.end();
  delay(1000);
  digitalWrite(led, 0);
  delay(1000);
  
  ESP.deepSleep(sleepTimeS * 1000000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
