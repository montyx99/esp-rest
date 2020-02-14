#pragma once

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <AsyncJson.h>
#include <list>

#define MAX_WIFI_SCANNER_SIZE 1024
namespace WifiScan {
    void ScanNetworks();
    AsyncJsonResponse* ListNetworks(AsyncWebServerRequest* request);
}

int getWifiSignalQuality(int RSSI);

#ifdef ESP8266        
uint8_t convertEncryptionType(uint8_t encryptionType);
#endif    
