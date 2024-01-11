#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int pinTurb = A0;
float v;
float kekeruhan;
float Vrata2;
float Vhasil;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("sensor SEN0189"); 
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  v = 0;
  for (int i = 0;i<800;i++) {
    v+=((float)analogRead(pinTurb)/1023)*5;
  }
  Vrata2 = v/800;
  Vhasil = roundf(Vrata2*10.0f)/10.0f;

  if(Vhasil<2.5){
    kekeruhan = 3000;
  }else{
    kekeruhan = - 1120.4*square(Vhasil)+5742.3*Vhasil-4353.8;
  }
  lcd.setCursor(0,0);
  lcd.print("tegangan");
  lcd.print(Vhasil);

  lcd.setCursor(0,1);
  lcd.print("kekeruhan");
  lcd.print(kekeruhan);

  Serial.print("tegangan :");
  Serial.print(Vhasil);
  Serial.print(" V");

  Serial.print("\t kekeruhan :");
  Serial.println(kekeruhan);
  delay(10);
}
