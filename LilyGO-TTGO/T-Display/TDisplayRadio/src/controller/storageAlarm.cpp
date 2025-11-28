#include "controller/storageAlarm.h" 
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

//#define FAKE_ALARM

#ifdef FAKE_ALARM
bool StorageAlarm::load() {
    _size = 12;
    for (uint8_t i = 0; i < _size; i ++) {
        _list[i].alarm = SET_ALARM_VOLUME(18, i*5, 3);
        _list[i].timer = nullptr;
        _list[i].controller = nullptr;
    }
    return true;
}
#else
bool StorageAlarm::load() {
    File f = LittleFS.open(FS_ALARM_FILE);
    if (!f) return false;
    JsonDocument  doc;
    DeserializationError error = deserializeJson(doc, f);
    f.close();
    if (error) return false;
    JsonArray array = doc.as<JsonArray>();
    if (array.size() > MAX_BLOCK_ALARM_SIZE) return false;
    _size = array.size();

    for (int i = 0; i < _size; i++) {
        JsonObject object = array[i].as<JsonObject>();

        _list[i].alarm.value = 0;
        _list[i].alarm.Hour = object["Hour"].as<int>();
        _list[i].alarm.Minute = object["Minute"].as<int>();
        _list[i].alarm.IsMute = object["Mute"].as<int>();
        _list[i].alarm.Volume = object["Volume"].as<int>();
        _list[i].alarm.Index = object["Index"].as<int>();
        _list[i].alarm.Buzzer = object["Buzzer"].as<int>();

        _list[i].alarm.Monday = object["Mo"].as<int>();
        _list[i].alarm.Tuesday= object["Tu"].as<int>();
        _list[i].alarm.Wednesday = object["We"].as<int>();
        _list[i].alarm.Thursday = object["Th"].as<int>();
        _list[i].alarm.Friday = object["Fr"].as<int>();
        _list[i].alarm.Saturday = object["Sa"].as<int>();
        _list[i].alarm.Sunday = object["Su"].as<int>();

        _list[i].timer = nullptr;
        _list[i].controller = nullptr;
    }
    return true;
}
#endif