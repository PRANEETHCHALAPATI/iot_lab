#include <Wire.h>

const int ledPin = 13;      // Built-in LED on many Arduino boards
const byte SLAVE_ADDR = 0x08;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  Wire.begin(SLAVE_ADDR);    // join i2c bus with address 0x08
  Wire.onReceive(receiveEvent);
}

void loop() {
  // Nothing needed in loop; action occurs in receiveEvent
  delay(50);
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    int b = Wire.read();    // read a byte (0..255)
    if (b == 1) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
}
