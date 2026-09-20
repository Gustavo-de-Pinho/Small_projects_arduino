int tempo = 1000;

void setup(){
  for(int pino =2; pino<= 6; pino++){
    pinMode(pino, OUTPUT);
  }
}

void loop(){
  for(int pino = 2; pino <= 6; pino++){
    digitalWrite(pino,HIGH);
    delay(tempo);
    digitalWrite(pino, LOW);
    delay(tempo);
  }

  for(int pino = 5; pino <= 3; pino--){
    digitalWrite(pino,HIGH);
    delay(tempo);
    digitalWrite(pino, LOW);
    delay(tempo);
  }
}