#define POTENTIOMETER_PIN 35 // ESP32 pin GIOP36 (ADC0) connected to Potentiometer pin
#define LED_PIN           21 // ESP32 pin GIOP21 connected to LED's pin
#define LED_PIN1 23
#define ANALOG_THRESHOLD  1000

void setup() {
  pinMode(LED_PIN, OUTPUT); // set ESP32 pin to output mode
}

void loop() {
  int analogValue = analogRead(POTENTIOMETER_PIN); // read the input on analog pin

  if (analogValue > ANALOG_THRESHOLD)
    digitalWrite(LED_PIN, HIGH); // turn on LED
    digitalWrite(LED_PIN1, HIGH); // turn on LED
  else
      digitalWrite(LED_PIN, LOW);  // turn off LED
   digitalWrite(LED_PIN1, LOW);  // turn off LED
}