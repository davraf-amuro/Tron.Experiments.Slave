#include <Arduino.h>
#include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <esp_now.h>
#include "config.h" //parametri globali
#include "lan_facade.h"

#include "espnow_facade.h"

unsigned long previousMillis = 0; // Memorizza l'ultimo tempo in cui il LED è stato aggiornato
const long interval = 1000; // Intervallo di tempo per il lampeggio del LED (1 secondo)
String macAddress; // Puntatore a char per memorizzare l'indirizzo MAC
// Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

OledDecorator oledDecorator(display);
void testDisplay();

void setup() {
    Serial.begin(115200); // Inizializza la comunicazione seriale

    //-------------------- Inizializzazione display OLED --------------------
    display.begin();
    Serial.println("Display inizializzato");
    oledDecorator.setRow2("Display Inizializzato", true);


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


    // pinMode(LED_FLASHING, OUTPUT);

    // Ottieni l'indirizzo MAC del dispositivo
    Serial.println("Accedo ai dati di rete");
    macAddress = GetMacAddress();
    Serial.println("Mac Address:" + macAddress);
    oledDecorator.setRow1("MA:" + macAddress);
    // oledDecorator.setRow2("MA:" + macAddress);
    oledDecorator.render();

    pinMode(BUTTON_K1, INPUT);

}

void loop() {
    if (digitalRead(BUTTON_K1) == LOW) {
        Serial.println("Pulsante K1 premuto");
        oledDecorator.setRow2("Porcone lanciato", true);
        // invia dati tramite esp-now
        struct_message message;
        strcpy(message.a, "Porcone lanciato");
        message.b = 123;
        message.c = 3.14;
        message.d = true;
        esp_err_t result = esp_now_send(peerInfo.peer_addr, (uint8_t *) &message, sizeof(message));
        if (result == ESP_OK) {
            oledDecorator.setRow3("Dati inviati con successo", true);
        } else {
            oledDecorator.setRow3("Errore di trasmissione", true);
        }

        delay(3000);
        oledDecorator.setRow2("");
        oledDecorator.setRow3(""); 
        oledDecorator.render();
    }

}

