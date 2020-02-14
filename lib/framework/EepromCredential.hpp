// #pragma once
// #include <Arduino.h>
// #include <EEPROM.h>

// const String PASS_START_STR = "PSS:";
// const String SSID_START_STR = "SSS:";
// const char EEPROM_FIELD_DELIMITER_CHR = ';';

// class EepromCredential {
//     public:
//         EepromCredential();
//         EepromCredential(bool loadCredentials);
//         String GetSsid();
//         String GetPassword();
//         bool CheckCredentialsExist();
//         bool UpdateCredentials(String ssid, String password);
//         byte GetMaxPasswordLength();
//         byte GetMaxSsidLength();
//         void SetMaxPasswordLength(u_int length);
//         void SetMaxPasswordLength(int length);
//         void SetMaxSsidLength(u_int length);
//         void SetMaxSsidLength(int length);
//         ~EepromCredential();
//     private:
        
//         void readCredentials();
//         static EepromCredential* instance;
//         int findInEeprom(String pattern, u_int length, u_int startIndex);
//         String readEEprom(int startIndex, int endIndex);
//         String readEepromData(String startPattern, u_int index);
//         bool writeEepromData(String password, String ssid);
//         bool validateCredentials(String password, String ssid);
//         String password;
//         String ssid;
//         u_int maxPasswordLength = 62; // The 802.1 technical limitation is 63 chars, reserved a char for 0x00 on the end
//         u_int maxSsidLength = 31; // The 802.1 technical limitation is 32 chars, reserved a char for 0x00 on the end
// };