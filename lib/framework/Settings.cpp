#include "Settings.hpp"

Settings::Settings() {}

Settings::~Settings() {}

void Settings::begin() {
    this->listSpiffsContent();
    if(!this->LoadSettings()) {
        this->CreateSettingsFile();
        this->LoadSettings();
    }
}

void Settings::listSpiffsContent() {
    Serial.println("HERE!!!");
    String str = "";
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
        str += dir.fileName();
        str += " / ";
        str += dir.fileSize();
        str += "\r\n";
    }
    Serial.print(str);
    Serial.println("File system mounted with success");
}

bool Settings::LoadSettings() {
    DynamicJsonDocument json(512);
    File file = SPIFFS.open(this->settingsFilename, "r");
    if(!file) {
        file.close();
        return false;
    }

    // while(file.available()) {
    //     //Lets read line by line from the file
    //     String line = file.readStringUntil('n');
    //     Serial.println(line);
    // }

    // file.seek(0);

    DeserializationError error = deserializeJson(json, file);
    file.close();
    if(error) {
        Serial.print("Error (2) - LoadSettings read error: ");
        Serial.println(error.c_str());
        return false;
    }
    
    this->settings.Wifi.Password = json["Wifi"]["Password"].as<String>();
    this->settings.Wifi.Ssid = json["Wifi"]["Ssid"].as<String>();
    this->settings.Wifi.StaticIp = json["Wifi"]["StaticIp"].as<String>();
    Serial.println("PASSWORD (2): " + this->settings.Wifi.Password);
    Serial.println("SSID (2): " + this->settings.Wifi.Ssid);
    return true;
}

bool Settings::CreateSettingsFile() {
    File file = SPIFFS.open(this->settingsFilename, "w");
    if (!file) {
        Serial.println(F("Failed to create file"));
        return false;
    }

    StaticJsonDocument<512> json;
    JsonObject Wifi = json.createNestedObject("Wifi");
    Wifi["Password"] = "";
    Wifi["Ssid"] = "";
    Wifi["StaticIp"] = "";
    if(!serializeJson(json, file)) {
        Serial.println("ERROR: failed write to " + this->settingsFilename);
        file.close();
        return false;
    }

    file.close();
    return true;
}

 bool Settings::OpenSettingsFile(JsonDocument& json) {
    File file = SPIFFS.open(this->settingsFilename, "r");
    DeserializationError error = deserializeJson(json, file);
    if(error) {
        Serial.print("Error (2) - LoadSettings read error: ");
        Serial.println(error.c_str());
        return false;
    }
    file.close();
    return true;
}

bool Settings::SaveWifiCredentials(String password, String ssid) {
    if(this->validateWifiCredentials(password, ssid)) {
        StaticJsonDocument<512> json;

        if(!OpenSettingsFile(json)) {
            if(!CreateSettingsFile()) {
                return false;
                
            }
            else if(!OpenSettingsFile(json)) {
                return false;
            }
        }

        SPIFFS.remove(this->settingsFilename);

        File file = SPIFFS.open(this->settingsFilename, "w");
        if (!file) {
            Serial.println(F("Failed to create file"));
            return false;
        }

        json["Wifi"]["Password"] = password;
        json["Wifi"]["Ssid"] = ssid;

        if(!serializeJson(json, file)) {
            Serial.println("ERROR: failed write to " + this->settingsFilename);
            file.close();
            json.~StaticJsonDocument();
            return false;
        }

        file.close();
        json.~StaticJsonDocument();
        return true;
    }
    else {
        Serial.println("ERROR: too long wifi credentials");
        return false;
    }
}

bool Settings::validateWifiCredentials(String password, String ssid) {
    bool result = (password.length() <= MAX_PASS_LENGTH && ssid.length() <= MAX_SSID_LENGTH);
    return result;
}