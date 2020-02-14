#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>

#define MAX_PASS_LENGTH 62 // The 802.1 technical limitation is 63 chars, reserved a char for 0x00 on the end
#define MAX_SSID_LENGTH 31 // The 802.1 technical limitation is 32 chars, reserved a char for 0x00 on the end

const String PASS_START_STR = "PSS:";
const String SSID_START_STR = "SSS:";
const char EEPROM_FIELD_DELIMITER_CHR = ';';

namespace SettingsStructures {
    struct SettingsWifi {
        String Password;
        String Ssid;
        String StaticIp;
    };

    struct SettingsJson {
        SettingsStructures::SettingsWifi Wifi;
    };
}

class Settings {
    public:
        Settings();
        Settings(bool loadSettings);
        
        void begin();
        String GetSsid();
        SettingsStructures::SettingsJson GetConfig() {return settings;};
        bool CheckCredentialsExist();
        bool SaveWifiCredentials(String password, String ssid);
        ~Settings();
    private:
        void listSpiffsContent();
        const String settingsFilename = "/config/settings.json";
        bool OpenSettingsFile(JsonDocument& json);
        bool CreateSettingsFile();
        bool LoadSettings();
        SettingsStructures::SettingsJson settings;
        void readCredentials();
        bool validateWifiCredentials(String password, String ssid);
        String password;
        String ssid;
};