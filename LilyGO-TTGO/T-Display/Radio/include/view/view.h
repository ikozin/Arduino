#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "main.h"
#include "logging.h"
#include "controller/controller.h"

class View {
    protected:
        View** _currentView;
        const char* _name;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
        TFT_eSprite* _sprite;
    protected:
        virtual void OnDrawHandle() = 0;
        static void ViewHandler(void* parameter);
    public:
        View(const char* name, View** currentView, SemaphoreHandle_t updateEvent = nullptr);
        virtual void Start(TFT_eSprite* sprite, uint16_t stackDepth = 4096) = 0;
        SemaphoreHandle_t GetEvent() const { return _updateEvent; };
};

template<typename Type>
class ViewT: public View {
    public:
        ViewT(const char* name, View** currentView, Type* ctrl, SemaphoreHandle_t updateEvent = nullptr): View(name, currentView, updateEvent) {
            assert(ctrl);
            _ctrl = ctrl;
        }
        virtual void Start(TFT_eSprite* sprite, uint16_t stackDepth = 1024) override {
            assert(sprite);
            _sprite = sprite;
            _ctrl->AddUpdateEvent(GetEvent());
            xTaskCreate(ViewHandler, this->_name, stackDepth, this, 100, &this->_task);
        }
    protected:
        Type* _ctrl;
};

// template<typename Type>
// class ViewAnimateT: public ViewT<Type> {
//     public:
//         ViewAnimateT(const char* name, View** currentView, Type* ctrl, uint16_t updateInterval = 1000, SemaphoreHandle_t updateEvent = nullptr):
//                 ViewT<Type>(name, currentView, ctrl, updateEvent) {
//             _updateInterval = updateInterval;
//         }
//     protected:
//         uint16_t _updateInterval;
//     protected:
//         virtual void OnGetDataHandle() = 0;
//         virtual void OnDrawHandle() = 0;

//         static void ViewHandler(void* parameter) {
//             assert(parameter);
//             ViewAnimateT<Type>* page = static_cast<ViewAnimateT<Type>*>(parameter);
//             TaskHandle_t _taskDraw;
//             xTaskCreate(DrawHandler, page->_name, 1024, page, 100, &_taskDraw);
//             for (;;) {
//                 xSemaphoreTake(page->_updateEvent, portMAX_DELAY);
//                 // Serial.printf("Update Event %s\r\n", page->_name);
//                 page->OnGetDataHandle();
//             }
//             vTaskDelete(_taskDraw);
//             vTaskDelete(page->_task);
//         }

//         static void DrawHandler(void* parameter) {
//             assert(parameter);
//             ViewAnimateT<Type>* page = static_cast<ViewAnimateT<Type>*>(parameter);
//             TickType_t xLastWakeTime = xTaskGetTickCount();
//             for (;;) {
//                 xTaskDelayUntil( &xLastWakeTime, page->_updateInterval / portTICK_PERIOD_MS);
//                 page->OnDrawHandle();
//             }
//         }
// };
