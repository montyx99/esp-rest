#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "RestApi.hpp"
#include "WifiService.hpp"

class EspJsonWs {
    public:
        EspJsonWs(AsyncWebServer* server, AsyncEventSource* events);
        void begin();
    private:
        WifiService wifiService;
        RestApi restApi;
        Settings settingsService;
};