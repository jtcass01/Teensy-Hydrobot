/**
 * @file
 * @brief 
 */

#include "Hydrobot.hpp"
#include "TeensyPins.h"
#include "Arduino.h"

/**
 * @brief \todo
 */
Hydrobot ::Hydrobot(TEENSY_PIN_ENUM relay_pin,
    MoistureSensor *sensors,
    uint8_t sensor_count,
    LiquidCrystal_I2C *lcd,
    float threshold,
    unsigned long pump_time,
    unsigned long soak_time) :
    _relay_pin(relay_pin),
    _sensors(sensors),
    _sensor_count(sensor_count),
    _lcd(lcd),
    _watering_threshold(threshold),
    _pump_run_time(pump_time),
    _soak_time(soak_time),
    _current_state(STATE_IDLE),
    _state_start_time(0),
    _last_average_moisture(0),
    _last_UI_Time(0) { }

void Hydrobot ::setup()
{
    // Setup Relay
    pinMode(_relay_pin, OUTPUT);
    // Relay is LOW-trigger (HIGH = OFF)
    digitalWrite(_relay_pin, HIGH); 

    // Setup sensors
    for (uint8_t sensor_index = 0; sensor_index < _sensor_count; sensor_index++)
    {
        _sensors[sensor_index].setup();
    }

    // Setup LCD
    _lcd->init();
    _lcd->backlight();
    _lcd->clear();

    // 2-second spash screen
    _lcd->setCursor(0, 0);
    _lcd->print("Hydrobot v1.0");
    _lcd->setCursor(0, 1);
    _lcd->print("Booting up....");
    delay(2000);
    _lcd->clear();
}

void Hydrobot ::tick()
{
    unsigned long current_time_ms = millis();

    // Read sensors
    _update_moisture();

    // Tick state machine
    switch (_current_state)
    {
        case STATE_IDLE:
        {
            if (_last_average_moisture < _watering_threshold)
            {
                // Turn pump on!
                digitalWrite(_relay_pin, LOW);
                _current_state = STATE_PUMPING;
                _state_start_time = current_time_ms;
            }
            break;
        }

        case STATE_PUMPING:
        {
            if (current_time_ms - _state_start_time >= _pump_run_time)
            {
                // Turn pump OFF
                digitalWrite(_relay_pin, HIGH);
                _current_state = STATE_SOAKING;
                _state_start_time = current_time_ms;
            }
            break;
        }

        case STATE_SOAKING:
        {
            if (current_time_ms - _state_start_time >= _soak_time)
            {
                _current_state = STATE_IDLE;
            }
            break;
        }
    }

    // Update UI
    if (current_time_ms - _last_UI_Time >= 1000)
    {
        _update_UI();
        _last_UI_Time = current_time_ms;
    }
}

/**
 * @brief \todo
 */
void Hydrobot ::_update_moisture()
{
    float total = 0;
    for (uint8_t i = 0; i < _sensor_count; i++)
    {
        total += _sensors[i].getPercentage();
    }

    _last_average_moisture = (_sensor_count > 0) ? (total / _sensor_count) : 0.0;
}

/**
 * @brief \todo
 */
void Hydrobot ::_update_UI()
{
    // Serial Output
    Serial.print("Moisture: ");
    Serial.print(_last_average_moisture);
    Serial.print("% | State: ");
    Serial.println(_current_state);

    // LCD Output - Line 1
    _lcd->setCursor(0, 0);
    _lcd->print("Moist: ");
    if (_last_average_moisture < 10.0) _lcd->print(" ");
    _lcd->print(_last_average_moisture, 1); 
    _lcd->print("%   "); // Clear trailing chars
    
    // LCD Output - Line 2
    _lcd->setCursor(0, 1);
    _lcd->print("Sys: ");
    switch (_current_state) {
    case STATE_IDLE:    _lcd->print("IDLE    "); break;
    case STATE_PUMPING: _lcd->print("PUMPING "); break;
    case STATE_SOAKING: _lcd->print("SOAKING "); break;
    }
}
