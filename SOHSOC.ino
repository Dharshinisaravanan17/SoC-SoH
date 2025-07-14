// Current Sensor Configuration (ACS712)
const int currentSensorPin = A0;
const float currentSensitivity = 0.066; // 66mV/A for ACS712-30A
float zeroOffset; // To be calculated

// Voltage Sensor Configuration (DC Voltage Sensor)
const int voltageSensorPin = A1;
const float voltageMultiplier = 5.0 * (25.0 / 5.0); // Adjust this as per sensor's divider ratio

// SoH Configuration
const float originalCapacity = 2000.0; // Original battery capacity in mAh (e.g., 2000mAh for a new 18650)
float usedCapacity = 0.0; // Capacity discharged over time
const float samplingTime = 2.5; // Time interval between measurements in seconds (same as delay time)

void setup() {
  Serial.begin(9600);

  // Initialize sensor pins
  pinMode(currentSensorPin, INPUT);
  pinMode(voltageSensorPin, INPUT);

  // Calibrate current sensor zero offset
  zeroOffset = calibrateZeroOffset();
  Serial.print("Zero Offset for Current Sensor: ");
  Serial.println(zeroOffset, 3);
}

void loop() {
  // Read Current Sensor
  int rawCurrentValue = analogRead(currentSensorPin);
  float sensorVoltage = (rawCurrentValue / 1023.0) * 5.0;
  float current = abs((sensorVoltage - zeroOffset) / currentSensitivity);

  // Read Voltage Sensor
  int rawVoltageValue = analogRead(voltageSensorPin);
  float voltage = (rawVoltageValue / 1023.0) * voltageMultiplier;

  // Calculate SoC
  float voltageCutoff = 2.8; // Cutoff voltage in volts
  float voltageFull = 4.2;   // Full charge voltage in volts
  float soc = ((voltage - voltageCutoff) / (voltageFull - voltageCutoff)) * 100.0;
  soc = constrain(soc, 0.0, 100.0);

  // Calculate SoH
  usedCapacity += (current * (samplingTime / 3600.0)); // Convert current (A) to mAh over time
  float soh = ((originalCapacity - usedCapacity) / originalCapacity) * 100.0;
  soh = constrain(soh, 0.0, 100.0);

  // Display Results
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V\t");

  Serial.print("Current: ");
  Serial.print(current, 3);
  Serial.print(" A\t");

  Serial.print("SoC: ");
  Serial.print(soc, 2);
  Serial.print(" %\t");

  Serial.print("SoH: ");
  Serial.print(soh, 2);
  Serial.println(" %");

  delay(2500); // 2.5-second delay for measurement frequency
}

// Function to calibrate zero offset for current sensor
float calibrateZeroOffset() {
  float sum = 0;
  int readings = 100; // Take 100 samples for averaging
  for (int i = 0; i < readings; i++) {
    sum += (analogRead(currentSensorPin) / 1023.0) * 5.0;
    delay(10); // Small delay between readings
  }
  return sum / readings;
}
