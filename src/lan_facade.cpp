#include "lan_facade.h"
#include <WiFi.h>

String GetMacAddress() {
    // Ottieni l'indirizzo MAC
    uint8_t mac[6];
    WiFi.macAddress(mac);

    // Converti l'indirizzo MAC in una stringa
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // Ritorna l'indirizzo MAC come String
    return String(macStr);
}