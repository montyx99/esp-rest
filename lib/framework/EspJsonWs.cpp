#include "EspJsonWs.hpp"

EspJsonWs::EspJsonWs(AsyncWebServer* server, AsyncEventSource* events) :
    settingsService(),
    restApi(server, events, &wifiService),
    wifiService(&settingsService) {}

void EspJsonWs::begin() {
    settingsService.begin();
    wifiService.begin(&settingsService);
}