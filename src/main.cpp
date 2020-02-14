#include <Arduino.h>
#include <FS.h>
#ifdef ESP32
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#endif
#include "RestApi.hpp"
#include "EspJsonWs.hpp"

AsyncWebServer server(80);
AsyncEventSource events("/events");
EspJsonWs espJsonWs(&server, &events);

void setup(){
    // analogWrite(LEDpin, 512); // PWM
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    SPIFFS.begin();
    while(!Serial);
    espJsonWs.begin();
}

void loop(){

}