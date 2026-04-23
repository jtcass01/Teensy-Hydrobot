/**
 * @file
 * @brief 
 */

#ifndef _HYDROBOT_
#define _HYDROBOT_

#include <stdint.h>
#include "TeensyPins.h"
#include "MoistureSensor.hpp"
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

// ─── System State ─────────────────────────────────────────────────────────
enum SYSTEM_STATE_ENUM : uint8_t
{
    STATE_IDLE    = 0x00,
    STATE_PUMPING = 0x01,
    STATE_SOAKING = 0x02
};

class Hydrobot {

public: 
    Hydrobot(TEENSY_PIN_ENUM relay_pin,
             MoistureSensor *sensors,
             uint8_t sensor_count,
             hd44780_I2Cexp *lcd,
             float threshold,
             unsigned long pump_time,
             unsigned long soak_time);

    void setup();
    void tick();

private:
    TEENSY_PIN_ENUM _relay_pin;
    MoistureSensor *_sensors;
    uint8_t _sensor_count;
    hd44780_I2Cexp *_lcd;

    float _watering_threshold;
    unsigned long _pump_run_time;
    unsigned long _soak_time;

    SYSTEM_STATE_ENUM _current_state;
    unsigned long _state_start_time;
    float _last_average_moisture;
    unsigned long _last_UI_Time;          // Tracks when the LCD was last updated.

    // Helper functions
    void _update_moisture();
    void _update_UI();

};

#endif // _HYDROBOT_