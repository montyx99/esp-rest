#pragma once
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266mDNS.h>
#endif
#include "Settings.hpp"

namespace WifiConstants {
    const IPAddress AP_IP_ADDRESS(192, 168, 4, 1);
    const IPAddress AP_NET_MASK(255, 255, 255, 0);
    const IPAddress STA_IP_ADDRESS(192, 168, 0, 150);
    const String HOST_NAME = "esp-json-ws";
    const byte DNS_PORT = 53;
    const byte BODY_READ_ERROR = 0;
    const byte SAVE_SUCCESS = 1;
    const byte SAVE_ERROR = 2;
}

class WifiService {
    public:
        WifiService(Settings* settings);
        ~WifiService();
        bool RestartWifi();
        byte SaveWifiCredentials(AsyncWebServerRequest* request, uint8_t *data);
        bool begin(Settings* service);

    private:
        DNSServer* dnsServer;
        Settings* settings;
        void setupMdns();
        void startApMode();
        void startStationMode(String ssid, String password);
        bool testWifi();
};
