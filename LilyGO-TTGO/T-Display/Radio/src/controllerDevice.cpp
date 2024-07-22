
#include <Wire.h>
#include "controllerDevice.h"

ControllerDevice::ControllerDevice(const char* name):
                    Controller(name), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _updateTimeInSec = 60;
    
    _temperature = 0;
    _humidity = 0;
    _pressure = 0;

    _dynamicValue = 0; 
    _staticValue = 0;
    _impulseValue = 0;
}

InitResponse_t ControllerDevice::OnInit() {
    if ( _bme.begin(BME280_PORT, &Wire)) {
        _bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X1, // temperature
                        Adafruit_BME280::SAMPLING_X1, // pressure
                        Adafruit_BME280::SAMPLING_X1, // humidity
                        Adafruit_BME280::FILTER_OFF);
    } else {
        return OnInitResultERROR;
    }
    if (_radSens.init())
    {
        return OnInitResultOK;
    } else {
        return OnInitResultERROR;
    }
}

bool ControllerDevice::OnIteration() {
    LOGN("ControllerDevice::OnIteration")

    _temperature = _bme.readTemperature();
    _humidity = _bme.readHumidity();
    _pressure = _bme.readPressure() / 1000.0F * 7.50062;

    _dynamicValue = _radSens.getRadIntensyDynamic(); 
    _staticValue = _radSens.getRadIntensyStatic();
    _impulseValue = _radSens.getNumberOfPulses();

    LOGN("ControllerDevice::getTemperature, %f", getTemperature())
    LOGN("ControllerDevice::getHumidity, %f", getHumidity())
    LOGN("ControllerDevice::getPressure, %f", getPressure())
    LOGN("ControllerDevice::getDynamic, %f", getDynamic())
    LOGN("ControllerDevice::getStatic, %f", getStatic())
    LOGN("ControllerDevice::getImpulse, %f", getImpulse())

    return true;
}
