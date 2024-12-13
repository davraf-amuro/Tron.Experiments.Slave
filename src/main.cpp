#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <esp_now.h>
#include "config.h" //parametri globali
#include "lan_facade.h"

#include "espnow_facade.h"

unsigned long previousMillis = 0; // Memorizza l'ultimo tempo in cui il LED è stato aggiornato
const long interval = 1000; // Intervallo di tempo per il lampeggio del LED (1 secondo)
String macAddress; // Puntatore a char per memorizzare l'indirizzo MAC
uint8_t broadcastAddress[] = {0xEC, 0x64, 0xC9, 0x86, 0x1A, 0x2C}; //EC:64:C9:86:1A:2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
bool autopilot = false;

OledDecorator oledDecorator(display);

void K1Pressed();
void DecodeResult(esp_err_t result);
void ClearDisplay(unsigned long delayTime);

void setup() {
    Serial.begin(115200); // Inizializza la comunicazione seriale

    //-------------------- Inizializzazione display OLED --------------------
    display.begin();
    Serial.println("Display inizializzato");
    oledDecorator.setRow2("Display Inizializzato", true);
    // Inizializza il puntatore globale a OledDecorator
    initOledDisplay(&oledDecorator);

    //-------------------- Inizializzazione ESP-NOW --------------------
    WiFi.mode(WIFI_STA);
    Serial.println("WiFi inizializzato in modalità STA");
    if (esp_now_init() != ESP_OK) {
        Serial.println("Errore durante l'inizializzazione di ESP-NOW");
        return;
    }
    // Registra le funzioni di callback
    esp_now_register_recv_cb(OnDataRecv);
    esp_now_register_send_cb(OnDataSent);
    Serial.println("ESP-NOW inizializzato");
    oledDecorator.setRow3("ESP-NOW inizializzato", true);

    // Ottieni l'indirizzo MAC del dispositivo
    Serial.println("Accedo ai dati di rete");
    macAddress = GetMacAddress();
    Serial.println("Mac Address:" + macAddress);
    oledDecorator.setRow1("MA:" + macAddress);
    // oledDecorator.setRow2("MA:" + macAddress);
    oledDecorator.render();

    // Registra il peer
    RegisterPeer(broadcastAddress);
    pinMode(BUTTON_K1, INPUT);
    pinMode(BUTTON_K4, INPUT);
}

void loop() {
    if (digitalRead(BUTTON_K4) == LOW) {
        Serial.println("Pulsante K4 premuto");
        oledDecorator.setRow4("", true);
        autopilot = !autopilot;
        delay(500);
    }

    if (autopilot) {
        // Serial.println("sei in autopilot mode");
        oledDecorator.setRow4("Autopilot", true);
        K1Pressed();
        ClearDisplay(500);  
    } else {
        // Serial.println("autopilot disattivato");
        if (digitalRead(BUTTON_K1) == LOW) {
            K1Pressed();
            ClearDisplay(2000);  
         }
    }
}

void ClearDisplay(unsigned long delayTime) {
    delay(delayTime);
    oledDecorator.setRow2("");
    oledDecorator.setRow3(""); 
    oledDecorator.render();
}

void K1Pressed() {
    Serial.println("Pulsante K1 premuto");
    oledDecorator.setRow2("Porcone lanciato", true);
    // invia dati tramite esp-now
    struct_message message;
    strcpy(message.a, "Porcone lanciato");
    message.b = 123;
    message.c = 3.14;
    message.d = true;
    // manda su serial la variabile broadcastAddress
    Serial.print("TO:");
    for (int i = 0; i < 6; i++) {
        Serial.print(broadcastAddress[i], HEX);
        Serial.print(":");
    }
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &message, sizeof(message));
    DecodeResult(result);
}

void DecodeResult(esp_err_t result) {
    switch (result) {
        case ESP_OK:
            oledDecorator.setRow3("Dati inviati con successo", true);
            Serial.println("Dati inviati con successo");
            break;
        case ESP_ERR_ESPNOW_NOT_INIT:
            oledDecorator.setRow3("ESP-NOW non è inizializzato", true);
            Serial.println("Errore di trasmissione: ESP-NOW non è inizializzato");
            break;
        case ESP_ERR_ESPNOW_ARG:
            oledDecorator.setRow3("Argomento non valido", true);
            Serial.println("Errore di trasmissione: Argomento non valido");
            break;
        case ESP_ERR_ESPNOW_INTERNAL:
            oledDecorator.setRow3("Errore interno", true);
            Serial.println("Errore di trasmissione: Errore interno");
            break;
        case ESP_ERR_ESPNOW_NO_MEM:
            oledDecorator.setRow3("Memoria insufficiente", true);
            Serial.println("Errore di trasmissione: Memoria insufficiente");
            break;
        case ESP_ERR_ESPNOW_NOT_FOUND:
            oledDecorator.setRow3("Peer non trovato", true);
            Serial.println("Errore di trasmissione: Peer non trovato");
            break;
        case ESP_ERR_ESPNOW_IF:
            oledDecorator.setRow3("Errore di interfaccia", true);
            Serial.println("Errore di trasmissione: Errore di interfaccia");
            break;
        default:
            oledDecorator.setRow3("Errore sconosciuto", true);
            Serial.println("Errore di trasmissione: Errore sconosciuto");
            Serial.println(result);
            break;
    }
}