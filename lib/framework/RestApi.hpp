#pragma once

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <AsyncJson.h>

#include "WifiScan.hpp"
#include "WifiService.hpp"

class RestApi {
    public:
        RestApi(AsyncWebServer* server, AsyncEventSource* events, WifiService* wifiService);
        ~RestApi();

        void begin();
    protected:
};