/*program ini didapatkan dari referensi robotikID*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define up digitalRead(2) == 0
#define down digitalRead(3) == 0
#define ok digitalRead(4) == 0
#define cancel digitalRead(5) == 0
#define lampu 6

char state;
int cd = 0;
unsigned long millisSebelum;
int hitungMulai;
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(lampu, OUTPUT);
  digitalWrite(lampu, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() > millisSebelum + 1000) {
    millisSebelum = millis();
    if (hitungMulai == 1) {
      cd--;
      digitalWrite(lampu, LOW);
      lcd.clear();
      if (cd == 0) {
        hitungMulai = 0;
        digitalWrite(lampu, HIGH);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("waktu habis!");
      }
    }
  }

  switch (state) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("countdown = ");
      lcd.print(cd);

      if (ok) {
        state = 1;
        digitalWrite(lampu, LOW);
        delay(100);
        lcd.clear();
      }
      if (up) {
        hitungMulai = 1;
        delay(100);
      }
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("cd = ");
      lcd.print(cd);
      if (up) {
        cd++;
        delay(100);
        lcd.clear();
      } else if (down) {
        cd--;
        delay(100);
        lcd.clear();
      }
      if (ok) {
        state = 0;
        delay(100);
        lcd.clear();
      } else if (cancel) {
        state = 0;
        cd = 0;
        delay(100);
        lcd.clear();
      }

      break;
  }
}