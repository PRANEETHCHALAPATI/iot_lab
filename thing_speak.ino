#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// Replace with your network credentials
const char* ssid = "m01";
const char* password = "12345678";

// Replace with your ThingSpeak API key
String apiKey = "INMKRPG1ND53G3P0";
const char* server = "http://api.thingspeak.com/update?";

// DHT settings
#define DHTPIN 4       // GPIO connected to DHT11 (e.g., GPIO4)
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Celsius

  // Check if reading was successful
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "api_key=" + apiKey + "&field1=" + String(t) + "&field2=" + String(h);
    http.begin(url);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Data sent successfully. Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data. HTTP response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected.");
  }

  delay(15000);  // ThingSpeak accepts updates every 15 seconds
}
