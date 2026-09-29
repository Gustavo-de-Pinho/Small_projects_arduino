#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const int buzzer = 7;
const int ldrPin = A1;
const int led = 8;
const int btnMais = 13;
const int btnMenos = 12;

int limiteLuz = 200;

bool btnMaisAnterior = HIGH;
bool btnMenosAnterior = HIGH;

unsigned long tempoMensagem = 0;
const unsigned long duracaoMensagem = 200;

char ultimoBotao = ' ';

bool mensagemBotaoAtiva = false;

unsigned long tempoBuzzer = 0;
bool estadoBuzzer = false;

const unsigned long intervaloBuzzer = 200;

int telaAtual = -1;
// -1 = nenhuma
//  0 = LDR
//  1 = SAIDA
//  2 = BOTAO +
//  3 = BOTAO -

int ultimoNivelExibido = -1;

unsigned long tempoAtualizacaoLdr = 0;
const unsigned long intervaloLdr = 100;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setBacklight(1);

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  pinMode(btnMais, INPUT_PULLUP);
  pinMode(btnMenos, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("Sistema iniciado");

  delay(500);

  lcd.clear();
}


// ALTERAR LIMITE
void alterarLimite(int &limiteLuz, char acao) {
  if (acao == '-' && limiteLuz >= 100) {
    limiteLuz -= 100;
  }
  else if (acao == '+' && limiteLuz <= 900) {
    limiteLuz += 100;
  }
}

void loop() {
  int nivelDeLuz = analogRead(ldrPin);

  bool btnMaisAtual = digitalRead(btnMais);
  bool btnMenosAtual = digitalRead(btnMenos);

  Serial.print("Nivel de Luz: ");
  Serial.println(nivelDeLuz);

  // BOTÃO (+)
  if (btnMaisAtual == LOW && btnMaisAnterior == HIGH) {
    alterarLimite(limiteLuz, '+');

    ultimoBotao = '+';
    tempoMensagem = millis();
    mensagemBotaoAtiva = true;
    telaAtual = 2;


    lcd.setCursor(0, 0);
    lcd.print("BOTAO +        ");

    lcd.setCursor(0, 1);
    lcd.print("Limite = ");
    lcd.print(limiteLuz);
    lcd.print("          ");
  }

  // BOTÃO (-)
  if (btnMenosAtual == LOW && btnMenosAnterior == HIGH) {
    alterarLimite(limiteLuz, '-');

    ultimoBotao = '-';
    tempoMensagem = millis();

    mensagemBotaoAtiva = true;
    telaAtual = 3;


    lcd.setCursor(0, 0);
    lcd.print("BOTAO -        ");

    lcd.setCursor(0, 1);
    lcd.print("Limite = ");
    lcd.print(limiteLuz);
    lcd.print("           ");
  }

  btnMaisAnterior = btnMaisAtual;
  btnMenosAnterior = btnMenosAtual;  

  // BUZZER E LED
if (nivelDeLuz < limiteLuz) {

  digitalWrite(led, HIGH);

  if (millis() - tempoBuzzer >= intervaloBuzzer) {
    tempoBuzzer = millis();

    estadoBuzzer = !estadoBuzzer;

    if (estadoBuzzer) {
      tone(buzzer, 1200);
    } else {
      tone(buzzer, 800);
    }
  }

} else {

  noTone(buzzer);
  digitalWrite(led, LOW);

  estadoBuzzer = false;
}

  // FINALIZA A MENSAGEM DO BOTAO
  if (mensagemBotaoAtiva &&
      millis() - tempoMensagem >= duracaoMensagem) {

    mensagemBotaoAtiva = false;
    telaAtual = -1;
  }

// LCD
if (!mensagemBotaoAtiva) {

  // SAIDA
  if (nivelDeLuz < limiteLuz) {

    // Só escreve quando muda para a tela SAIDA
    if (telaAtual != 1) {

      lcd.setCursor(5, 0);
      lcd.print("SAIDA      ");
      lcd.setCursor(1, 1);
      lcd.print("DE EMERGENCIA");

      telaAtual = 1;
    }
  }

  // LDR
  else {

    // Atualiza a leitura em intervalos
    if (telaAtual != 0 ||
        millis() - tempoAtualizacaoLdr >= intervaloLdr) {

      tempoAtualizacaoLdr = millis();

      // Só escreve se o valor realmente mudou
      if (nivelDeLuz != ultimoNivelExibido || telaAtual != 0) {

        lcd.setCursor(0, 0);
        lcd.print("Energia estavel");
        lcd.print("      ");
        lcd.setCursor(0, 1);
        lcd.print("    LDR: ");
        lcd.print(nivelDeLuz);
        lcd.print("       ");



        ultimoNivelExibido = nivelDeLuz;
        telaAtual = 0;
      }
    }
  }
}
  }
