#include <PZEM004Tv30.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
PZEM004Tv30 pzem(D3, D4); // Software Serial pin 8 (RX) & 9 (TX)
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);

  lcd.setCursor(0,0); //Mengatur letak tulisan ke LCD
  lcd.print("Program HC-SR04"); //Tampilan pada LCD
  lcd.setCursor(0,1); //Mengatur letak tulisan ke LCD
  lcd.print("Ultrasonik");
  lcd.setCursor(0,2);
  lcd.print("m zadid ilmi");
  lcd.setCursor(0,3);
  lcd.print("2GD4TE");
  delay(1000);
  lcd.clear();
}
void loop() {
  float voltage = pzem.voltage();
  if (voltage != NAN) {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");

    lcd.setCursor(0,0); //Mengatur letak tulisan ke LCD
    lcd.print("volt:");lcd.print(voltage);lcd.print("V");  
  } else {
    Serial.println("Error reading voltage");
  }
  float current = pzem.current();
  if (current != NAN) {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");

    lcd.setCursor(0,1); //Mengatur letak tulisan ke LCD
    lcd.print("curr:");lcd.print(current);lcd.print("A");  
  } else {
    Serial.println("Error reading current");
  }
  float power = pzem.power();
  if (current != NAN) {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");

    lcd.setCursor(0,2); //Mengatur letak tulisan ke LCD
    lcd.print("power:");lcd.print(power);lcd.print("W");  
  } else {
    Serial.println("Error reading power");
  }
  float energy = pzem.energy();
  if (current != NAN) {
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println("kWh");

    lcd.setCursor(0,3); //Mengatur letak tulisan ke LCD
    lcd.print("energy:");lcd.print(energy,3);lcd.print("kwh");  
  } else {
    Serial.println("Error reading energy");
  }
  float frequency = pzem.frequency();
  if (current != NAN) {
    Serial.print("Frequency: ");
    Serial.print(frequency, 1);
    Serial.println("Hz");
  } else {
    Serial.println("Error reading frequency");
  }
  float pf = pzem.pf();
  if (current != NAN) {
    Serial.print("PF: ");
    Serial.println(pf);
  } else {
    Serial.println("Error reading power factor");
  }
  Serial.println();
  delay(2000);
}