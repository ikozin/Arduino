#pragma once

#include "main.h"

#define EventListMax    (3)

class IUpdater {
    protected:
        SemaphoreHandle_t   _eventList[EventListMax] { nullptr, nullptr, nullptr };
    public:
        bool AddUpdateEvent(SemaphoreHandle_t event) {
            for (int i = 0; i < EventListMax; i++) {
                if (_eventList[i] == nullptr) {
                    _eventList[i] = event;
                    return true;
                }
            }
            return false;
        }
    protected:
        void FireUpdateEvent() {
            for (int i = 0; i < EventListMax && _eventList[i] != nullptr; i++) {
                xSemaphoreGive(_eventList[i]);
            }
        }
};
