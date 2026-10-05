const int buzzer = 7;
const int ldrPin = A1;
const int led = 8;
const int btnMais = 13;
const int btnMenos = 12;

int limiteLuz = 200;

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  pinMode(btnMais, INPUT_PULLUP);
  pinMode(btnMenos, INPUT_PULLUP);

  Serial.println("Sistema iniciado");
}


// ALTERAR LIMITE
void alterarLimite(char acao) {

  if (acao == '-' && limiteLuz > 100) {
    limiteLuz -= 100;
  }

  else if (acao == '+' && limiteLuz < 900) {
    limiteLuz += 100;
  }
}

void tocarAlarme() {
  tone(buzzer, 1200);
  delay(200);

  tone(buzzer, 800);
  delay(200);
}


void loop() {

  int nivelDeLuz = analogRead(ldrPin);


  // BOTAO +
  if (digitalRead(btnMais) == LOW) {

    alterarLimite('+');

    Serial.print("BOTAO + | Limite = ");
    Serial.println(limiteLuz);

    delay(200);
  }


  // BOTAO -
  if (digitalRead(btnMenos) == LOW) {

    alterarLimite('-');

    Serial.print("BOTAO - | Limite = ");
    Serial.println(limiteLuz);

    delay(200);
  }
  

  // BUZZER E LED
  if (nivelDeLuz < limiteLuz) {
    digitalWrite(led, HIGH);
	tocarAlarme();
  }
  else {
    noTone(buzzer);
    digitalWrite(led, LOW);
  }


  // MONITOR SERIAL
  Serial.print("LDR: ");
  Serial.print(nivelDeLuz);

  Serial.print(" | Limite: ");
  Serial.print(limiteLuz);

  if (nivelDeLuz < limiteLuz) {
    Serial.println(" | SAIDA DE EMERGENCIA");
  }
  else {
    Serial.println(" | Iluminacao estavel");
  }

  delay(150);
}