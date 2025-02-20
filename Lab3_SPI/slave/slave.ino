#include <SPI.h>

volatile boolean received = false;
volatile char receivedData;

void setup() {
    pinMode(MISO, OUTPUT);  // MISO must be output for SPI slave
    SPI.begin();            // Initialize SPI as slave
    SPCR |= _BV(SPIE);      // Enable SPI interrupt
    Serial.begin(9600);
}

// Interrupt Service Routine (ISR) for SPI
ISR(SPI_STC_vect) {  
    receivedData = SPDR;  // Read received data
    received = true;
    SPDR = 'B';  // Send response back to master
}

void loop() {
    if (received) {
        Serial.print("Slave received: ");
        Serial.println(receivedData);
        received = false;
    }
}
