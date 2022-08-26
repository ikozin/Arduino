#ifndef _VIEW_H_
#define _VIEW_H_

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "main.h"

class View{
    protected:
        TFT_eSPI* _tft;
        View** _currentView;
        const char* _name;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
    public:
        View(const char* name, TFT_eSPI* tft, View** currentView);
        void Start(SemaphoreHandle_t updateEvent);
        virtual void OnHandle() = 0;
        SemaphoreHandle_t GetEvent() const { 
            assert(_updateEvent);
            return _updateEvent;
        };
    private:
        static void ViewHandler(void* parameter);
};

#endif  //_VIEW_H_