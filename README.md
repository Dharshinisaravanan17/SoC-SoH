# SoC-SoH
Arduino-based State of Charge &amp; State of Health estimation for Li-ion battery
# Arduino-Based Battery SoC & SoH Estimation

This project uses an Arduino Uno with voltage and current sensors to estimate the **State of Charge (SoC)** and **State of Health (SoH)** of a 2000mAh lithium-ion battery. The code reads voltage and current values and performs simple calculations to provide an estimated SoC and track battery condition over time.

## Features
- Voltage sensing via analog input
- Current sensing using external sensor module
- Real-time calculation of battery SoC and SoH
- Suitable for basic battery diagnostics and educational demos

## Hardware Used
- Arduino Uno
- Voltage divider circuit
- Voltage sensor
- Current sensor (e.g., ACS712 / INA219)
- 2000mAh Li-ion battery

## Note
This is a simple implementation for demonstration and prototyping purposes. Accuracy may vary based on sensor type, wiring, and calibration.

