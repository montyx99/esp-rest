#include "WifiService.hpp"

WifiService::WifiService(Settings* settings) {
    this->settings = settings;
}
WifiService::~WifiService() {}

bool WifiService::RestartWifi() {
    WiFi.disconnect();
    return begin(this->settings);
}

byte WifiService::SaveWifiCredentials(AsyncWebServerRequest* request, uint8_t *data) {
    StaticJsonDocument<200> doc;
    DeserializationError err = deserializeJson(doc, data);

    if(err) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
        return WifiConstants::BODY_READ_ERROR;
    }
    else {
        String ssidStr = doc["ssid"].as<String>();
        String passwordStr = doc["password"].as<String>();
        if(this->settings->SaveWifiCredentials(passwordStr, ssidStr)) {
            return WifiConstants::SAVE_SUCCESS;
        }
    }
    Serial.println("ERROR: Cannot save credentials");
    return WifiConstants::SAVE_ERROR;
}

bool WifiService::begin(Settings* service){
    SettingsStructures::SettingsJson config = service->GetConfig();
    if(config.Wifi.Password && config.Wifi.Ssid) {
        Serial.print("Initial SSID: ");
        Serial.println(config.Wifi.Ssid);
        Serial.print("Initial PASS: ");
        Serial.println(config.Wifi.Password);

        startStationMode(config.Wifi.Ssid, config.Wifi.Password);
        if(!testWifi()) {
            startApMode();
            return false;
        }
        else {
            setupMdns();
            return true;
        }
    }
    else {
        startApMode();
        return false;
    }
}

void WifiService::setupMdns() {
    MDNS.addService("http","tcp",80);
    MDNS.begin(WifiConstants::HOST_NAME);
}

void WifiService::startApMode() {
    WiFi.mode(WIFI_AP);
    WiFi.hostname(WifiConstants::HOST_NAME);
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(WifiConstants::AP_IP_ADDRESS, WifiConstants::AP_IP_ADDRESS, WifiConstants::AP_NET_MASK) ? "Ready" : "Failed!");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("My IP Address: ");
    Serial.println(myIP);
    if(!dnsServer) {
        dnsServer = new DNSServer;
    }
    dnsServer->start(WifiConstants::DNS_PORT, "*", myIP);
}

void WifiService::startStationMode(String ssid, String password) {
    WiFi.mode(WIFI_STA);
    WiFi.hostname(WifiConstants::HOST_NAME);
    WiFi.begin(ssid, password);
}

bool WifiService::testWifi() {
    Serial.print("Waiting for Wifi to connect...");
    for(int i = 0; i < 10; ++i) {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Done.");
            return true;
        }
        delay(500);
        Serial.print(WiFi.status());
    }
    Serial.println("Connect timed out, opening AP");
    return false;
}