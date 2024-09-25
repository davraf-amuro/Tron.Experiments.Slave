#include "chip_facade.h"

void printChipInfoes() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("");
  Serial.println("");

  // Informazioni generali del chip
  Serial.println("Informazioni sul chip ESP32:");
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  // Stampa il modello del chip
  const char* model;
  switch (chip_info.model) {
    case CHIP_ESP32:
      model = "ESP32";
      break;
    case CHIP_ESP32S2:
      model = "ESP32-S2";
      break;
    case CHIP_ESP32S3:
      model = "ESP32-S3";
      break;
    case CHIP_ESP32C3:
      model = "ESP32-C3";
      break;
    case CHIP_ESP32H2:
      model = "ESP32-H2";
      break;
    default:
      model = "Unknown";
      break;
  }
  Serial.printf("Modello: %s\n", model);

  // Stampa le caratteristiche del chip
  Serial.print("Caratteristiche: ");
  if (chip_info.features & CHIP_FEATURE_WIFI_BGN) {
    Serial.print("WiFi ");
  }
  if (chip_info.features & CHIP_FEATURE_BLE) {
    Serial.print("BLE ");
  }
  if (chip_info.features & CHIP_FEATURE_BT) {
    Serial.print("BT ");
  }
  if (chip_info.features & CHIP_FEATURE_EMB_FLASH) {
    Serial.print("Flash Integrata ");
  }
  if (chip_info.features & CHIP_FEATURE_EMB_PSRAM) {
    Serial.print("PSRAM Integrata ");
  }
  Serial.println();

  Serial.printf("Core: %d\n", chip_info.cores);
  Serial.printf("Revisione silicio: %d\n", chip_info.revision);
  Serial.printf("Velocità CPU: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Flash integrata: %d MB %s\n", spi_flash_get_chip_size() / (1024 * 1024), (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "interna" : "esterna");
  Serial.printf("WiFi supportato: %s\n", (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "Si" : "No");
  Serial.printf("Bluetooth supportato: %s\n", (chip_info.features & CHIP_FEATURE_BT) ? "Si" : "No");
}