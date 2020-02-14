#include "EepromCredential.hpp"

// EepromCredential::EepromCredential(bool loadCredentials) {
//     if(loadCredentials) {
//         readCredentials();
//     }
// }

// EepromCredential::EepromCredential(){}

// bool EepromCredential::CheckCredentialsExist() {
//     Serial.println("pass length: " + password.length());
//     Serial.println("ssid length: " + password.length());
//     return password.length() && ssid.length();
// }

// /** Store WLAN credentials to EEPROM */
// bool EepromCredential::UpdateCredentials(String ssid, String password) {
//     bool result = writeEepromData(password, ssid);
//     return result;
// }

// String EepromCredential::GetPassword() {return password;}
// String EepromCredential::GetSsid() {return ssid;}
// byte EepromCredential::GetMaxPasswordLength() {return maxPasswordLength;}
// byte EepromCredential::GetMaxSsidLength() {return maxSsidLength;}

// void EepromCredential::SetMaxPasswordLength(u_int length) {
//     maxPasswordLength = length;
// }

// void EepromCredential::SetMaxPasswordLength(int length) {
//     maxPasswordLength = u_int(length);
// }

// void EepromCredential::SetMaxSsidLength(u_int length) {
//     maxSsidLength = length;
// }

// void EepromCredential::SetMaxSsidLength(int length) {
//     maxSsidLength = u_int(length);
// }

// /** Load WLAN credentials from EEPROM */
// void EepromCredential::readCredentials() {
//     EEPROM.begin(512);
//     password = readEepromData(PASS_START_STR, 0);
//     Serial.println("EEPROM prePASS: " + password);
//     if(password.length()) {
//         ssid = readEepromData(SSID_START_STR, password.length());
//         EepromCredential credentials;
//         this->password = password;
//         this->ssid = ssid;
//         EEPROM.end();
//     }
//     Serial.println("EEPROM PASS: " + this->password);
//     Serial.println("EEPROM SSID: " + this->ssid);
// }

// int EepromCredential::findInEeprom(String pattern, u_int length, u_int startIndex) {
//     u_int index = -1;
//     String subString;
//     u_int i = startIndex;
//     while(EEPROM.length() > (length + startIndex) && i < EEPROM.length() - length && subString != pattern) { // 511: max eeprom size -4 for the looked starter strings
//         subString = "";
//         subString += char(EEPROM.read(i)) + char(EEPROM.read(i + 1)) + char(EEPROM.read(i + 2));

//         if(subString == pattern) {
//             index = i;
//         }
//         ++i;
//     }
//     return index;
// }

// String EepromCredential::readEEprom(int startIndex, int endIndex) {
//     String str;
//     for(int i = startIndex; i < endIndex; ++i) {
//         str += EEPROM.read(i);
//     }
//     return str;
// }

// String EepromCredential::readEepromData(String startPattern, u_int startIndex) {
//     String str;
//     Serial.println("startPattern: " + startPattern);
//     // Find start string position
//     int index = findInEeprom(startPattern, startPattern.length(), startIndex);
//     Serial.println("index: " + String(index));
//     int endIndex = -1;
//     if(index > -1) {
//         endIndex = findInEeprom(String(EEPROM_FIELD_DELIMITER_CHR), 1, index + 4);
//     }
//     Serial.println("endIndex: " + String(endIndex));
//     if(endIndex > -1 && endIndex > index + startPattern.length()) {
//         str = readEEprom(index + startPattern.length(), endIndex);
//     }
//     return str;
// }

// bool EepromCredential::writeEepromData(String newPassword, String newSsid) {
//     String password;
//     if(validateCredentials(newPassword, newSsid)) {
//         this->password = newPassword;
//         this->ssid = newSsid;
//         EEPROM.begin(512);
//         String credentialData = PASS_START_STR + this->password + EEPROM_FIELD_DELIMITER_CHR +  SSID_START_STR + this->ssid + EEPROM_FIELD_DELIMITER_CHR;
//         Serial.println("EEPROM Save String: " + credentialData);
//         for(u_int i = 0; i < credentialData.length(); ++i) {
//             if(credentialData[i] != EEPROM.read(i)) {
//                 EEPROM.write(i, credentialData[i]);
//             }
//         }
//         if(EEPROM.commit()) {
//             Serial.println("EEPROM Save success");
//         }
//         else {
//             Serial.println("EEPROM Save error");
//         }
//         password = readEepromData(PASS_START_STR, 0);
//         Serial.println("Written pass: " + password);
//         EEPROM.end();
//         return true;
//     }
//     return false;
// }

// bool EepromCredential::validateCredentials(String password, String ssid) {
//     bool result = (password.length() <= maxPasswordLength && ssid.length() <= maxSsidLength);
//     return result;
// }

// EepromCredential::~EepromCredential() {}
