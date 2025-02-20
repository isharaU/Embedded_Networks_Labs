#include <SPI.h>

#define SS_PIN 10  

void setup() {
    pinMode(SS_PIN, OUTPUT);
    SPI.begin();  
    Serial.begin(9600);
}

void loop() {
    digitalWrite(SS_PIN, LOW);  // Enable slave
    char receivedData = SPI.transfer('A');  // Send 'A' and receive response
    Serial.print("Master received: ");
    Serial.println(receivedData);
    digitalWrite(SS_PIN, HIGH); // Disable slave
    delay(1000);
}
