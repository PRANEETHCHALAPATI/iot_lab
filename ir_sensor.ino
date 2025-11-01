#define ledpin 5
#define irpin 4
	void setup() {
  	// put your setup code here, to run once:
  	pinMode (ledpin,OUTPUT);
  	pinMode (irpin,INPUT);
  	Serial.begin(9600);

	}

	void loop() {
  	// put your main code here, to run repeatedly:
  	if(digitalRead(irpin)==0){
    	digitalWrite(ledpin,HIGH);
    	Serial.print("Detected\n");
     	delay(500);
    
    	}
    	else{
     	 digitalWrite(ledpin,LOW);
	     Serial.print("Not detected\n");
      
    	}
  

}