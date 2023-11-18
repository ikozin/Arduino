#include "DevicePackage.h"

DevicePackage::DevicePackage(const char * title, TDevice** list, size_t count) {
    _title = title;
    _list = list;
    _count = count;
}

void DevicePackage::next(size_t step) {
    _selected += step;
    _selected = constrain(_selected, 0, _count - 1);
}

void DevicePackage::prev(size_t step) {
    _selected -= step;
    _selected = constrain(_selected, 0, _count - 1);
}

void DevicePackage::display(GyverDisplay& display) {
    int line = 0;
    if (_count > 6) {
        line = (_selected - 3 >= 0) ? _selected - 3 : 0;
        line = (_selected >= _count - 3) ? _count - 7: line;
    }
    display.clear();
    display.setCursor(0, 0);
    display.println(_title);
    for (int i = 0; i < 7; i++) {
        if (line + i == _count) break;
        display.invertText(_selected == line + i);
        display.println(_list[line + i]->menu());
    }
    display.invertText(false);
    display.update();
} 

int DevicePackage::test(GyverDisplay& display) {
    return _list[_selected]->test(display);
}

int DevicePackage::test(GyverDisplay& display, int index) {
    _selected = constrain(index, 0, _count - 1);
    return test(display);
}
