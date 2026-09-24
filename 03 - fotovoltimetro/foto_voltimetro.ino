// Definição dos Pinos
const int ledPin = 5;  
const int ldrPin = A3; 

int limiteLuz = 900;                                                                                                                                   

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int nivelDeLuz = analogRead(ldrPin);
  
  if (nivelDeLuz > limiteLuz) {
    digitalWrite(ledPin, HIGH); // Acende o LED
  } else {
    digitalWrite(ledPin, LOW);  // Apaga o LED
  }
  
}