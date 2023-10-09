#include "DevicePackage.h"

DevicePackage::DevicePackage(const char * title, TDevice** list, size_t count) {
    _title = title;
    _list = list;
    _count = count;
}

int DevicePackage::menu(void) {
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
    return cmd.toInt();
}

int DevicePackage::test(int index) {
    if (index == -1) return -1;
    return _list[index]->test();
}
