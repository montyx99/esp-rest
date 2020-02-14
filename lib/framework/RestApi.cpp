#include "RestApi.hpp"
#include "WifiService.hpp"

RestApi::RestApi(AsyncWebServer* server, AsyncEventSource* events, WifiService* wifiService) {
    Serial.print("Setting up generic API Endpoints...");
    events->onConnect([](AsyncEventSourceClient *client){
        client->send("hello!", NULL, millis(), 1000);
    });
    
    server->addHandler(events);
  
    server->on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", String(ESP.getFreeHeap()));
    });

    server->on("/api/v1/wifiscan", HTTP_GET, [](AsyncWebServerRequest *request){
        WifiScan::ScanNetworks();
        request->send(202);
    });

    server->on("/api/v1/wifilist", HTTP_GET, [](AsyncWebServerRequest* request) {
        AsyncJsonResponse *response = WifiScan::ListNetworks(request);
        if(!response) {
            request->send(202);
        }
        else {
            request->send(response);
        }
    });

    server->on(
        "/api/v1/wifisetup",
        HTTP_POST,
        [](AsyncWebServerRequest * request){},
        NULL,
        [wifiService](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
            switch(wifiService->SaveWifiCredentials(request, data)) {
                case WifiConstants::SAVE_SUCCESS:
                    Serial.println("Saved!");
                    request->send(200, "text/plain", "Saved!");
                    wifiService->RestartWifi();
                    break;
                case WifiConstants::SAVE_ERROR:
                    Serial.println("Failed to update credentials!");
                    request->send(500, "text/plain", "Failed to update credentials!");
                    break;
                case WifiConstants::BODY_READ_ERROR:
                    Serial.println("Cannot read request body!");
                    request->send(400, "text/plain", "Cannot read request body!");
                    break;
            }
        }
    );

    server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server->onNotFound([](AsyncWebServerRequest *request){
        Serial.printf("NOT_FOUND: ");
            if(request->method() == HTTP_GET)
                Serial.printf("GET");
            else if(request->method() == HTTP_POST)
                Serial.printf("POST");
            else if(request->method() == HTTP_DELETE)
                Serial.printf("DELETE");
            else if(request->method() == HTTP_PUT)
                Serial.printf("PUT");
            else if(request->method() == HTTP_PATCH)
                Serial.printf("PATCH");
            else if(request->method() == HTTP_HEAD)
                Serial.printf("HEAD");
            else if(request->method() == HTTP_OPTIONS)
                Serial.printf("OPTIONS");
            else
                Serial.printf("UNKNOWN");
        Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

        if(request->contentLength()){
            Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
            Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
        }

        int headers = request->headers();
        int i;
        for(i=0;i<headers;i++){
            AsyncWebHeader* h = request->getHeader(i);
            Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
        }

        int params = request->params();
        for(i=0;i<params;i++){
            AsyncWebParameter* p = request->getParam(i);
            if(p->isFile()){
                Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
            } else if(p->isPost()){
                Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
            } else {
                Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
            }
        }

        request->send(404);
    });
    server->begin();
    Serial.println("Done.");
}

RestApi::~RestApi() {};
    