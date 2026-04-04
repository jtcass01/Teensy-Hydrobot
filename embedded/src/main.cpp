#include <Arduino.h>
#include "Hydrobot.hpp"

const uint8_t RELAY_PIN = 2;
MoistureSensor sensors[] = {
  MoistureSensor(TEENSY_PIN_A0, 800, 400),
  MoistureSensor(TEENSY_PIN_A1, 800, 400),
  MoistureSensor(TEENSY_PIN_A2, 800, 400),
  MoistureSensor(TEENSY_PIN_A3, 800, 400)
};
const uint8_t SENSOR_COUNT = sizeof(sensors) / sizeof(sensors[0]);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Hydrobot hydrobot(TEENSY_PIN_RELAY, sensors, SENSOR_COUNT, &lcd, 30.0, 60000, 300000);

void setup() {
  Serial.begin(9600);
  hydrobot.setup();
}

void loop() {
  hydrobot.tick();
}
