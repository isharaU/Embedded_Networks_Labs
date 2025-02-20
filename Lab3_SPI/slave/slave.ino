#include <SPI.h>

void setup() {
  // Initialize SPI as Slave
  SPCR |= _BV(SPE);  // Enable SPI
  
  // Turn on interrupts (optional)
  SPCR |= _BV(SPIE);
  
  // Initialize Serial for debugging
  Serial.begin(9600);
}

// SPI interrupt routine
ISR(SPI_STC_vect) {
  // Read the received data from the SPI Data Register
  byte receivedData = SPDR;
  
  // Send a response back to the master (e.g., received data + 1)
  SPDR = receivedData + 1;  // Example: Send back received data + 1
  
  // Print the received data in decimal
  Serial.print("Received: ");
  Serial.println(receivedData);
}

void loop() {
  // The loop can be empty since the SPI communication is handled by the ISR
}