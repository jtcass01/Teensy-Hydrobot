#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "Hydrobot.hpp"

const uint8_t RELAY_PIN = 2;

MoistureSensor sensors[] = {
  MoistureSensor(TEENSY_PIN_A0, 760, 375),
  MoistureSensor(TEENSY_PIN_A1, 770, 375),
  MoistureSensor(TEENSY_PIN_A2, 750, 365),
  MoistureSensor(TEENSY_PIN_A3, 760, 665)
};

const uint8_t SENSOR_COUNT = sizeof(sensors) / sizeof(sensors[0]);

hd44780_I2Cexp lcd;
Hydrobot hydrobot(TEENSY_PIN_RELAY, sensors, SENSOR_COUNT, &lcd, 55.0f, 300000UL, 150000UL);

void readSensors() {
  int a0_value = analogRead(A0);
  int a1_value = analogRead(A1);
  int a2_value = analogRead(A2);
  int a3_value = analogRead(A3);
  Serial.printf("{a0: %d, a1: %d, a2: %d, a3: %d}\n", a0_value, a1_value, a2_value, a3_value);
  delay(100);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  hydrobot.setup();
}

void loop() {
  hydrobot.tick();
}