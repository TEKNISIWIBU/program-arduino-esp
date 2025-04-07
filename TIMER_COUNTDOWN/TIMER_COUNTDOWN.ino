#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinLed = 2;
const int buttonTambah = 7;
const int buttonKurang = 6;
const int buttonSet = 5;
const int buttonStop = 4;

int minute = 0;
int m, s = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin();
pinMode(pinLed,OUTPUT);
pinMode(buttonTambah,INPUT_PULLUP);
pinMode(buttonKurang,INPUT_PULLUP);
pinMode(buttonSet,INPUT_PULLUP);
pinMode(buttonStop,INPUT_PULLUP);

lcd.setCursor(1,0);
lcd.print("TEKNISI WIBU");
lcd.setCursor(1,1);
lcd.print("project timer");
delay(3000);
lcd.clear();
}

void loop() {
  //tampilan awal
  lcd.setCursor(0, 0);
  lcd.print("Timer :");
  lcd.setCursor(9, 0);
  lcd.print("0"); lcd.print(" :"); lcd.print(" 0");
  //atur waktu
  if (digitalRead(buttonSet) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Atur Waktu");
    delay(1500);

    //Input waktu menit
    while (digitalRead(buttonSet) == HIGH) {
      if (digitalRead(buttonTambah) == LOW) {
        if (minute >= 20) {
          minute = 0;
        } else {
          minute++;
        }
      }
      if (digitalRead(buttonKurang) == LOW) {
        if (minute < 1) {
          minute = 20;
        } else {
          minute--;
        }
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menit : ");
      Serial.println(minute);
      lcd.print(minute);
      delay(400);
    }

    lcd.clear();
    m = minute;
    s = 0;
    lcd.setCursor(4, 0);
    lcd.print("Mulai");
    delay(500);
    //menampilkan waktu yang telah diatur
    for (m; m >= 0; m--) {
      for (s; s >= 0; s--) {
        digitalWrite(pinLed, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Timer : ");
        lcd.print(m);
        lcd.print(" : ");
        lcd.print(s);
        if (digitalRead(buttonStop) == LOW) {
          goto timeStop;
        }
        delay(1000);
      }
      s = 59;
    }
    digitalWrite(pinLed, LOW);
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Selesai");
    while (digitalRead(buttonStop) == HIGH) {
      lcd.setCursor(4, 0);
      lcd.print("Selesai");
      delay(500);
      lcd.clear();
    }

    timeStop:
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Stop");
    delay(1000);
    lcd.clear();
  }
}
