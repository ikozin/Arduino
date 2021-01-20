//https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system.html#api-reference

// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
  print_system_info();
  Serial.println();
  Serial.println();
  delay(5000);
}

esp_chip_info_t chip_info;
char text[128];

void print_system_info()
{
  sprintf(text, "SDK Version:\t%s", esp_get_idf_version());
  Serial.println(text);

  sprintf(text, "Free Heap Size:\t%d", esp_get_free_heap_size());
  Serial.println(text);
  
  esp_chip_info(&chip_info);
  Serial.print("Chip Model:\t");
  switch (chip_info.model)
  {
    case 1:
      Serial.println("ESP32");
      break;
    case 2:
      Serial.println("ESP32-S2");
      break;
    case 4:
      Serial.println("ESP32-S3");
      break;
    case 5:
      Serial.println("ESP32-C3");
      break;
    default:
      Serial.println("Unknown");
      break;
  }

  sprintf(text, "CPU Cores:\t%d", chip_info.cores);
  Serial.println(text);
  sprintf(text, "Chip Revision:\t%d", chip_info.revision);
  Serial.println(text);

  sprintf(text, "Feature Flags:\t%X", chip_info.features);
  Serial.println(text);
  if (chip_info.features & CHIP_FEATURE_EMB_FLASH)
    Serial.print("[Embedded Flash] ");
  if (chip_info.features & CHIP_FEATURE_WIFI_BGN)
    Serial.print("[2.4GHz WiFi] ");
  if (chip_info.features & CHIP_FEATURE_BLE)
    Serial.print("[Bluetooth LE] ");
  if (chip_info.features & CHIP_FEATURE_BT)
    Serial.print("[Bluetooth Classic] ");
}
