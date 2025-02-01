#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "esp_timer.h"
#include "main.h"
#include "logging.h"
#include "controller/controller.h"

class View;

class ViewSettig {
    public:
        ViewSettig(TFT_eSPI *tft, TFT_eSprite* sprite, View** currentView) {
            _tft = tft;
            _sprite = sprite;
            _currentView = currentView;
        }
    private:
        TFT_eSPI *_tft;
        TFT_eSprite* _sprite;
        View** _currentView;
    public:
        TFT_eSPI * getDisplay() const { return _tft; }
        TFT_eSprite * getSprite() const { return _sprite; }
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
            ViewT* page = static_cast<ViewT*>(parameter);
            xSemaphoreGive(page->_updateEvent);
        }
};