#include <Wire.h>
#include "rgb_lcd.h" 

rgb_lcd lcd;

int buzzer = 7;
int limiteLuz = 600;
const int ldrPin = A1;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  lcd.setRGB(255, 255, 255);

  pinMode(buzzer, OUTPUT);
}

void loop() {
  int nivelDeLuz = analogRead(ldrPin);
  
  if (nivelDeLuz < limiteLuz) {
    tone(buzzer, 1000); // ativa o buzzer
     lcd.print("EXIT");
  } else {  
    noTone(buzzer);     // desliga o buzzer
    lcd.print("LUZ");
  }
  delay(50);
}
