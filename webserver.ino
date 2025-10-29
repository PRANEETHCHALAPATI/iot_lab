#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "wifi_name";
const char* password = "pswd";
void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
Serial.println("Connecting");
while(WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}
void loop() {
if(WiFi.status()== WL_CONNECTED){
HTTPClient http;
http.begin("http://192.168.243.153:8000/get-sensor?temperature=243");
int httpCode = http.GET();
if (httpCode > 0) { 
String payload = http.getString();
Serial.println(httpCode);
Serial.println(payload);
}
else {
Serial.println("Error on HTTP request");
}
http.end();
}else{
}
delay(10000);
}
