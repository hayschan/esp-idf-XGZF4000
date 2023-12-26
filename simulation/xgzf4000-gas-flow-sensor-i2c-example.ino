// Custom chips playground
// See https://link.wokwi.com/custom-chips-alpha for more info

#include <Wire.h>

const int SENSOR_ADDRESS = 0x50; // I2C address of the gas flow sensor

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Initialize I2C
}

void loop() {
  // Request 2 bytes from the sensor
  if (Wire.requestFrom(SENSOR_ADDRESS, 2) != 2) {
    Serial.println("Sensor not responding. Ensure correct setup of xgzf4000.chip.c");
    delay(500);
  } else {
    // Read two bytes (high byte and low byte)
    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();

    // Combine the two bytes to form a 16-bit value
    uint16_t flowRate = (highByte << 8) | lowByte;

    // Print the flow rate value
    Serial.print("Flow rate: ");
    Serial.println(flowRate);
    delay(1000);
  }
}
