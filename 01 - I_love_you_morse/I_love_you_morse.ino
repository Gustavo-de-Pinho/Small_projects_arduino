int pinoLed = 2;

// Padrão universal código morse (peguei da wiki)
int tempoPonto = 150;       // ponto
int tempoTraco = 450;       // 3x ponto
int espacoLetra = 450;      // 3x o ponto
int espacoPalavra = 1050;   // 7x o ponto

void setup() {
  pinMode(2, OUTPUT);
}

void ponto() {
  digitalWrite(pinoLed, HIGH);
  delay(tempoPonto);
  digitalWrite(pinoLed, LOW);
  delay(tempoPonto);
}

void traco() {
  digitalWrite(pinoLed, HIGH);
  delay(tempoTraco);
  digitalWrite(pinoLed, LOW);
  delay(tempoPonto);
}

void loop() {
  //I
  ponto();ponto();
  delay(espacoPalavra);

  //LOVE
  ponto();traco();ponto();ponto();
  delay(espacoLetra);
  traco();traco();traco();
  delay(espacoLetra);
  ponto();ponto();ponto();traco();
  delay(espacoLetra);
  ponto();
  delay(espacoPalavra);

  //YOU
  traco();ponto();traco();traco();
  delay(espacoLetra);
  traco();traco();traco();
  delay(espacoLetra);
  ponto();ponto();traco();
  delay(4000);
  }
