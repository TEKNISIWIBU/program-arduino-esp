#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int nilai = 0;
float setpoint;
const int kipas = 12;
//mengautur variable ds18b20
const int oneWireBusPin = 10;
OneWire oneWire(oneWireBusPin);
DallasTemperature Sensor(&oneWire);
//fungsi waktu millis
unsigned long lastmillis;
#define interval 1000
// ----------------------------------------setting fungsi keypad-------------------------//
const byte ROWS = 4;
const byte COLS = 4;
float setpoin = 0;
float input = 0;
char hexaKeys[ROWS][COLS] = {
  { 'D', 'C', 'B', 'A' },
  { '#', '9', '6', '3' },
  { '0', '8', '5', '2' },
  { '*', '7', '4', '1' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
//-----------------------------------------------------------------------------------------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("pengatur silo");
  lcd.setCursor(0, 1);
  lcd.print("dengan keypad");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - lastmillis > interval) {
    Sensor.requestTemperatures();
    float celsius = Sensor.getTempCByIndex(0);
    lcd.setCursor(0, 0);
    lcd.print("suhu:");
    lcd.print(celsius) + lcd.print("    ");
    Serial.println(celsius);
  if (celsius > setpoint) {
      digitalWrite(buzzerPin, HIGH); // Nyalakan buzzer
    } else {
      digitalWrite(buzzerPin, LOW); // Matikan buzzer
    }
    //realtime millis
    lastmillis = millis();
  }

  char customeKey = customKeypad.getKey();
  if (customeKey) {
    if (customeKey >= '0' && customeKey <= '9') {
      input = input * 10 + (customeKey - '0');  //membuat karakter float
      lcd.setCursor(0, 1);
      lcd.print("set:");
      lcd.setCursor(4, 1);
      lcd.print(input);
    } else if (customeKey == '#') {  //menghapus karakter
      input = 0;
      //lcd.clear();
    } else if (customeKey == '*') {  //reset
      input = 0;
      setpoint = 0;
      //lcd.print("                          ");
      lcd.setCursor(0, 0);
      lcd.print("data terestar");
    } else if (customeKey == 'A') {
      setpoint = input;
      lcd.setCursor(0, 1);
      lcd.print("setpoin:");
      lcd.print(setpoint);
    }    
  }
}
