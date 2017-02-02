// HC-SR501 Motion Detector

int ledPin = 7;  // LED on Pin 13 of Arduino
int pirPin = 8; // Input for HC-S501

int pirValue = 0;

void setup() {
  Serial.begin(57600);
    
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
 
  digitalWrite(ledPin, LOW);
  

  
}

void loop() {
  pirValue = digitalRead(pirPin);
  Serial.println(pirValue);
  digitalWrite(ledPin, pirValue);
  delay(1000);
}

