/**
 * @file
 * @brief This file defines the enumeration TEENSY_PIN_ENUM, which represents all the pin assignments on the Teensy board.
 */

#ifndef _TEENSY_H_
#define _TEENSY_H_

#include <stdint.h>
#include <Arduino.h>

#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @brief Enum for all the pin assignments on the Teensy board.
 *
 * This enum includes assignments for motor direction and step pins, linear encoder pins, speed potentiometer pin,
 * up and down button pins for each motor, UART TX and RX pins, and limit switch pins.
 */
typedef enum : uint8_t {
    TEENSY_PIN_RELAY = 2,
    TEENSY_PIN_A0 = A0,
    TEENSY_PIN_A1 = A1,
    TEENSY_PIN_A2 = A2,
    TEENSY_PIN_A3 = A3,
    TEENSY_PIN_A4 = A4,
    TEENSY_PIN_A5 = A5,
    TEENSY_PIN_A6 = A6,
    TEENSY_PIN_A7 = A7,
    TEENSY_PIN_A8 = A8,
    TEENSY_PIN_A9 = A9,
    TEENSY_PIN_A10 = A10,
    TEENSY_PIN_A11 = A11,
    TEENSY_PIN_A12 = A12,
    TEENSY_PIN_A13 = A13,
    TEENSY_PIN_A14 = A14,
    TEENSY_PIN_A15 = A15,
    TEENSY_PIN_A16 = A16,
    TEENSY_PIN_A17 = A17,
    TEENSY_PIN_UNDEFINED = 39
} TEENSY_PIN_ENUM;

#ifdef __cplusplus
    }
#endif

#endif // _TEENSY_H_