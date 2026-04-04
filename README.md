# Teensy-Hydrobot: Automated Watering System

An automated, precision watering system designed specifically for a single fabric pot. It uses a Teensy 4.1 microcontroller to average readings from capacitive soil moisture sensors, triggering a slow-flow peristaltic pump to water the plant. 

The system uses a non-blocking "Pump and Soak" state machine to prevent water runoff—a common issue with fabric pots—allowing capillary action to distribute the moisture before re-evaluating the soil state.

## Hardware Components

* **Microcontroller:** [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)
* **Moisture Sensors:** 4x Capacitive Soil Moisture Sensors (SKU: SEN0193)
  * *Note: Measures via capacitive sensing rather than resistive, preventing corrosion.*
* **Pump:** 5V to 6V DC Peristaltic Liquid Pump (Adafruit Product ID: 3910)
  * *Specs: 100 mL/min flow rate, ~500mA current draw. Self-priming. Fluid never touches the motor.*
* **Relay:** 5V 2-Channel Relay Module (Low-Level Trigger)
* **Power Supply:** External 5V, 2A DC Power Supply
* **Tubing:** Silicone tubing (3.5mm inner diameter, 5mm outer diameter)
* **Container:** Single Fabric Pot

## Important Power & Safety Notes

1. **Sensor Voltage Limit:** The SEN0193 sensors can operate at 3.3V–5.5V, but the Teensy 4.1 analog pins **are not 5V tolerant**. The sensors MUST be powered from the Teensy's 3.3V pin so their analog output does not exceed 3.3V.
2. **Pump Power:** The peristaltic pump draws up to 500mA. It must be powered by the external 5V power supply via the relay, *not* directly from the Teensy's 5V/VIN pin, to prevent brownouts or damage to the microcontroller.
3. **Common Ground:** The external 5V power supply ground must be tied to the Teensy's GND pin.
