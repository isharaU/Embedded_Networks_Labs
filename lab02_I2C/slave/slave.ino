#include <Wire.h>

#define SLAVE_ADDR 8

void setup() {
  Wire.begin(SLAVE_ADDR); // Join I2C bus with address 8
  Wire.onReceive(receiveEvent); // Register event for receiving data
  Wire.onRequest(requestEvent); // Register event for sending data
  Serial.begin(9600);
  Serial.println("Slave ready");
}

void loop() {
  delay(100);
}

// Function to run when data is received from master
void receiveEvent(int bytes) {
  Serial.print("Received: ");
  while (Wire.available()) {
    char c = Wire.read(); // Receive byte
    Serial.print(c);
  }
  Serial.println();
}

// Function to run when master requests data
void requestEvent() {
  Wire.write("Hello Master"); // Send response to master
}
