#include <SPI.h>

void setup() {
  // Initialize SPI as Master
  SPI.begin();
  
  // Set SS pin as output
  pinMode(SS, OUTPUT);
  
  // Initialize Serial for debugging
  Serial.begin(9600);
}

void loop() {
  // Data to be sent to the slave (decimal number)
  byte dataToSend = 123;  // Example data (123 in decimal)
  
  // Select the slave by setting SS low
  digitalWrite(SS, LOW);
  
  // Send data to the slave
  byte receivedData = SPI.transfer(dataToSend);
  
  // Deselect the slave by setting SS high
  digitalWrite(SS, HIGH);
  
  // Print the sent and received data in decimal
  Serial.print("Sent: ");
  Serial.print(dataToSend);
  Serial.print(" | Received: ");
  Serial.println(receivedData);
  
  // Wait for a second before sending the next data
  delay(1000);
}