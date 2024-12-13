#include "espnow_facade.h"
#include "oled_ssd1315.h"

struct_message incomingMessage;
esp_now_peer_info_t peerInfo;
static char macReceiver[18];
OledDecorator* oleDisplay = nullptr; // Inizializza il puntatore a nullptr

// Funzione di inizializzazione per impostare oleDisplay
void initOledDisplay(OledDecorator* display) {
    oleDisplay = display;
}

// Funzione per registrare un peer
void RegisterPeer(uint8_t broadcastAddress[]) {
    // Setta il MAC Address del peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    // Setta il peer come non bloccante
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    // Aggiunge il peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Errore durante l'aggiunta del peer");
        return;
    }
}

// Callback per la ricezione dei dati
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    memcpy(&incomingMessage, data, sizeof(incomingMessage));
    snprintf(macReceiver, sizeof(macReceiver), "%02X:%02X:%02X:%02X:%02X:%02X", 
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print("ESP-NOW incoming from: ");
    Serial.println(macReceiver);
    Serial.print("Bytes received: ");
    Serial.println(data_len);
    Serial.print("Char: ");
    Serial.println(incomingMessage.a);
    Serial.print("Int: ");
    Serial.println(incomingMessage.b);
    Serial.print("Float: ");
    Serial.println(incomingMessage.c);
    Serial.print("Bool: ");
    Serial.println(incomingMessage.d);

    oleDisplay->setRow4(incomingMessage.a, true);
    delay(1000);
    oleDisplay->setRow4("", true);
}

// Callback per l'invio dei dati
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}