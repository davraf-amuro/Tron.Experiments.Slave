#ifndef ESPNOW_FACADE_H
#define ESPNOW_FACADE_H

#include <esp_now.h>
#include <WiFi.h>

// Struttura per i dati da inviare/ricevere
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

// Variabile per memorizzare i dati ricevuti
extern struct_message incomingMessage;
// Create peer interface
extern esp_now_peer_info_t peerInfo;

void RegisterPeer(uint8_t broadcastAddress[]);

// Callback per la ricezione dei dati
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);

// Callback per l'invio dei dati
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif // ESPNOW_FACADE_H