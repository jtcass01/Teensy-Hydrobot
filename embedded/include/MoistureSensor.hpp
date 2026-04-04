/**
 * @file
 * @brief 
 */

#ifndef _MOISTURE_SENSOR_
#define _MOISTURE_SENSOR_

#include "TeensyPins.h"

class MoistureSensor {

public: 
    MoistureSensor(TEENSY_PIN_ENUM analog_pin,
                   uint16_t air_calibration_value,
                   uint16_t water_calibration_value);
    void setup();
    float getPercentage();

private:
    TEENSY_PIN_ENUM _pin;
    uint16_t _air_calibration_value;
    uint16_t _water_calibration_value;
};

#endif // _MOISTURE_SENSOR_