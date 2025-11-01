
int LED= 5; // Define LED pin
int PIR= 4; // Define PIR pin
int val= 0; // Initializing the value as zero at the beginning
  
void setup() {
  

pinMode(LED, OUTPUT);
pinMode(PIR, INPUT);
Serial.begin(9600);
}

void loop() {

val = digitalRead(PIR);  
if(val == HIGH){
  digitalWrite(LED, HIGH); 

  Serial.println("Movement Detected\n"); // Print this text in Serial Monitor
}
else 
{
  digitalWrite(LED, LOW);

  Serial.println("Movement not Detected\n");
}
}