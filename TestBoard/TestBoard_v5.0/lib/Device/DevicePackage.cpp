#include "DevicePackage.h"

DevicePackage::DevicePackage(const char * title, TDevice** list, size_t count) {
    _title = title;
    _list = list;
    _count = count;
}

int DevicePackage::menu(void) {
    size_t index = 0;
    for (;;) {
        delay(200);
        Serial.println();
        Serial.println(_title);
        for (size_t i = 0; i < _count; i++) {
#ifdef BUTTON_CONTROL
            Serial.print((index == i)? "-> ": "   ");
#endif
            Serial.print(i);
            Serial.print(F(" - "));
            Serial.println(_list[i]->menu());
        }
#ifdef BUTTON_CONTROL
        for (;;) {
            if (digitalRead(PIN_BUTTON) == LOW) return -1;
            if (digitalRead(PIN_BUTTON_ENTER) == LOW) return index;
            if (digitalRead(PIN_BUTTON_UP) == LOW) {
                if (index > 0) {
                    index --;
                    break;
                }
            }
            if (digitalRead(PIN_BUTTON_DOWN) == LOW) {
                if (index < (_count - 1)) {
                    index ++;
                    break;
                }
            }
        }
#else
        Serial.print("Введите команду:");
        while (!Serial.available());
        String cmd = Serial.readStringUntil('\r');
        Serial.println(cmd);
        Serial.println();
        return cmd.toInt();
#endif
    }
}

int DevicePackage::test(int index) {
    if (index == -1) return -1;
    return _list[index]->test();
}
