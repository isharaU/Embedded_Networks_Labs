#include <Wire.h>

#define SLAVE_ADDR 8

void setup() {
  Wire.begin(); // Join I2C bus as master
  Serial.begin(9600);
}

void loop() {
  // Send data to slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write("Hello Slave");  // Message to slave
  Wire.endTransmission();
  Serial.println("Message sent to slave");

  // Request data from slave
  Wire.requestFrom(SLAVE_ADDR, 13);  // Request 13 bytes from slave

  while (Wire.available()) {
    char c = Wire.read(); // Receive a byte as character
    Serial.print(c);
  }
  Serial.println();

  delay(2000); // Wait for 2 seconds before sending again
}
