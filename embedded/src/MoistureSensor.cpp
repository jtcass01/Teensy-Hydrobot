/**
 * @file
 * @brief 
 */

#include "MoistureSensor.hpp"
#include "TeensyPins.h"
#include "Arduino.h"

/**
 * @brief \todo
 */
MoistureSensor ::MoistureSensor(TEENSY_PIN_ENUM analog_pin,
                                uint16_t air_calibration_value,
                                uint16_t water_calibration_value)
    : _pin(analog_pin),
      _air_calibration_value(air_calibration_value),
      _water_calibration_value(water_calibration_value) { }

/**
 * @brief \todo
 */
void MoistureSensor ::setup()
{
    pinMode(_pin, INPUT);
}

/**
 * @brief \todo
 */
float MoistureSensor ::getPercentage()
{
    int raw_value = analogRead(_pin);
    float percentage = map(raw_value, _air_calibration_value, 
                           _water_calibration_value, 0, 100);
    return constrain(percentage, 0.0, 100.0);
}
