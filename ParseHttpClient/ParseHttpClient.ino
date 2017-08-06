#include <DHT.h>

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
ESP8266WiFiMulti WiFiMulti;
const int led = 13;

void setup() {
    pinMode(led, OUTPUT);
    dht.begin();
    WiFiMulti.addAP("Xiaomi", "ss13880419943");

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        String target = "http://portal.xiandusi.com:1337/example/classes/Temperature";
        //String target = "http://192.168.31.164:8012/example/Temperature";
        http.begin(target); //HTTP
        digitalWrite(led, 1);

        http.addHeader("X-Parse-Application-Id", "123456");
        http.addHeader("X-Parse-REST-API-KEY", "123456");
        http.addHeader("Content-Type", "application/json");
        String data = "{\"t\":T, \"h\":H, \"tag\": 2}";
        data.replace("T",String(t));
        data.replace("H", String(h));
        int httpCode = http.POST(data);
        

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
        digitalWrite(led,0);
    }

    delay(10000);
}

