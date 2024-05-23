#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define RXD2 16//pin RX ESP32 yang digunakan untuk sensor PZEM(TX) 
#define TXD2 17//pin TX ESP32 yang digunakan untuk sensor PZEM(RX)
 //pengaturan lcd 20x4
LiquidCrystal_I2C lcd(0x3F, 20, 4);//insialisasi library LiquidCrystal_I2C.h sebagai lcd
//pengaturan library untuk pzem
PZEM004Tv30 pzem(&Serial2, RXD2, TXD2);//insialisasi library PZEM004Tv30 sebagai pzem 
float overVoltage = 213.40;
#define relay 19 //definisi pin 18 sebagai relay 
//pengaturan untuk sensor ds1820
const int oneWireBusPin = 4;
OneWire oneWire(oneWireBusPin);
DallasTemperature Sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);//insialisasi library pzem 
  pzem.resetEnergy();//mereset pzem bila mengalami pemadaman
  pinMode(relay,OUTPUT);
  lcd.begin();//mengaktifkan library lcd
  
  //membuat karakter pertama saat muncul di lcd
  lcd.setCursor(0,0); //Mengatur letak tulisan ke LCD
  lcd.print("implementasi PZEM004T"); //Tampilan pada LCD
  lcd.setCursor(6,1); //Mengatur letak tulisan ke LCD
  lcd.print("proteksi");
  lcd.setCursor(0,2);
  lcd.print("motor listrik 1phase");
  lcd.setCursor(0,3);
  lcd.print("//----------------//");
  delay(2000);
  lcd.clear();//membersihkan character di lcd
}
 
void loop() {
  float voltage = pzem.voltage();
  if (voltage != NAN) {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");

  lcd.setCursor(0,0); //Mengatur letak tulisan ke LCD
  lcd.print("V:"); lcd.print(voltage); lcd.print("V"); //Tampilan pada LCD
  } else {
    Serial.println("Error reading voltage");
  }
  float current = pzem.current();
  if (current != NAN) {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");

    lcd.setCursor(0,1); //Mengatur letak tulisan ke LCD
    lcd.print("A:"); lcd.print(current); lcd.print("A"); //Tampilan pada LCD
  } else {
    Serial.println("Error reading current");
  }
  float power = pzem.power();
  if (current != NAN) {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");

    lcd.setCursor(0,2); //Mengatur letak tulisan ke LCD
    lcd.print("P:"); lcd.print(power); lcd.print("W"); //Tampilan pada LCD
  } else {
    Serial.println("Error reading power");
  }
  float energy = pzem.energy();
  if (current != NAN) {
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println("kWh");

    lcd.setCursor(0,3); //Mengatur letak tulisan ke LCD
    lcd.print("E:"); lcd.print(energy,3); lcd.print("kWh"); //Tampilan pada LCD
  } else {
    Serial.println("Error reading energy");
  }
  Serial.println();
  delay(1000);
//proteksi untuk relay 
  lcd.setCursor(10,1);
  lcd.print("!!PROTEC!!");
if(voltage > overVoltage ){
  digitalWrite(relay,HIGH);
  lcd.setCursor(10,2);
  lcd.print("OVERVOLTA");
}else {
  digitalWrite(relay,LOW);
  lcd.setCursor(10,2);
  lcd.print("         ");
}
  //menampilkan nilai dari sensor ds18b20
Sensors.requestTemperatures();//MENGAMBIL nilai temperatur dari library ds18b20
float celsius = Sensors.getTempCByIndex(0);//presentasi nilai sensor dalam celcius
//menampilkan nilai dari sensor
lcd.setCursor(10,0);
lcd.print("C:");
lcd.print(celsius);
lcd.print((char)223); 
}