#include <WiFi.h>
#include <PubSubClient.h>

#define Ledpin 13
#define IRpin 14

// WIFI credentials
const char* ssid = "ssid";
const char* password = "password";

// MQTT Broker IP address
const char* mqtt_server = "192.168.173.114";

char tempString[20];  // Buffer to hold the message
WiFiClient espClient;
PubSubClient client(espClient);

// Callback function when a message is received
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  
  // Create a temporary string to hold the message
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }

  Serial.print("Message: ");
  Serial.println(messageTemp);

  // Check if the received topic is the acknowledgment topic
  if (String(topic) == "ESP32/Acknowledgement") {
    Serial.println("Acknowledgment received from Raspberry Pi!");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Ledpin, OUTPUT);
  pinMode(IRpin, INPUT);

  // Connect to WiFi
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT client and set callback
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Connect to the MQTT broker
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("espClient")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe("ESP32/Acknowledgement");  // Subscribe to acknowledgment topic
    } else {
      Serial.print("Failed to connect, state: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void loop() {
  // Ensure the MQTT client stays connected and processes incoming messages
  client.loop();

  bool IRstatus = digitalRead(IRpin);
  if (IRstatus == true) {
    digitalWrite(Ledpin, LOW);  // Turn off the LED
    strcpy(tempString, "LED OFF");
  } else {
    digitalWrite(Ledpin, HIGH);  // Turn on the LED
    strcpy(tempString, "LED ON");
  }

  // Publish the status to the MQTT topic
  client.publish("ESP32/Temperaturedataread", tempString);


  delay(2000);
}
