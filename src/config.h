// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include "oled_ssd1315.h"

// parametri per il display OLED 0.96
// #define OLED_ADDR 0x3C
// #define OLED_WIDTH 128
// #define OLED_HEIGHT 64
// #define OLED_RESET -1 // Reset pin (usato -1 se non collegato)

#define BUTTON_K1 34
#define BUTTON_K4 27

extern const long interval; // Dichiarazione della variabile globale
extern unsigned long currentMillis; // Dichiarazione della variabile globale
extern OledDecorator oledDecorator; // Dichiarazione dell'oggetto globale

#endif
