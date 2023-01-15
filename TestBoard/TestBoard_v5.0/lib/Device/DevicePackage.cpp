#include "DevicePackage.h"

DevicePackage::DevicePackage(const char * title, TDevice** list, size_t count) {
    _title = title;
    _list = list;
    _count = count;
}

void DevicePackage::menu(void) {
    _selected = -1;
    Serial.println();
    Serial.println(_title);
    for (size_t i = 0; i < _count; i++) {
        Serial.print(i);
        Serial.print(F(" - "));
        Serial.println(_list[i]->menu());
    }
    Serial.print("Введите команду:");
    while (!Serial.available());
    String cmd = Serial.readStringUntil('\r');
    Serial.println(cmd);
    Serial.println();
    _selected = cmd.toInt();    
}

int DevicePackage::test(void) {
    if (_selected == -1) return -1;
    return _list[_selected]->test();
}
