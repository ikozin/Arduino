#pragma once

#include <Arduino.h>
#include "display.h"
#include "esp_timer.h"
#include "main.h"
#include "logging.h"
#include "controller/controller.h"

class View;

class ViewSettig {
    public:
        ViewSettig(LGFX* tft, View** currentView) {
            _tft = tft;
            _currentView = currentView;
        }
    private:
        LGFX* _tft;
        View** _currentView;
    public:
        LGFX* getDisplay() const { return _tft; }
        View** getCurrentView() const { return _currentView; }
};

class View {
    public:
        View(const char* name, ViewSettig* setting, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        const char* _name;
        const ViewSettig* _setting;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
    protected:
        virtual void OnInit() {};
        virtual void OnDrawHandle() = 0;
        static void ViewHandler(void* parameter);
    public:
        virtual void Start(uint16_t stackDepth = 4096) = 0;

        SemaphoreHandle_t GetEvent() const { return _updateEvent; };
        const ViewSettig* getSetting() const { return _setting; };
};

class ViewT: public View {
    public:
        ViewT(const char* name, ViewSettig* setting, Controller* ctrl, uint64_t period = 0, SemaphoreHandle_t updateEvent = nullptr) :
                View(name, setting, updateEvent) {
            assert(ctrl);
            _ctrl = ctrl;
            _period = period;
            _timer = nullptr;
        }
        virtual void Start(uint16_t stackDepth = 1024) override {
            if (_period == 0) {
                _ctrl->AddUpdateEvent(GetEvent());
            } else {
                const esp_timer_create_args_t periodic_timer_args = {
                    .callback = &TimerCallback,
                    .arg = static_cast<void*>(this),
                    .name = this->_name,
                    .skip_unhandled_events = true,
                };
                esp_timer_create(&periodic_timer_args, &_timer);
                esp_timer_start_periodic(_timer, _period);
            }
            xTaskCreate(ViewHandler, this->_name, stackDepth, this, 100, &this->_task);
        }
    protected:
        Controller* _ctrl;
        uint64_t _period;
        esp_timer_handle_t _timer;
    protected:
        static void TimerCallback(void* parameter) {
            ViewT* view = static_cast<ViewT*>(parameter);
            xSemaphoreGive(view->_updateEvent);
        }
};