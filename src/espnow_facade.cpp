#include "espnow_facade.h"

struct_message incomingMessage;
esp_now_peer_info_t peerInfo;

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
    
}

// Callback per l'invio dei dati
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}