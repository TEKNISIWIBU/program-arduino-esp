#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

//konfigurasi pin dan variable flow sensor 
int TURBINE;
int Hsensor = 3;
int Calc;
//class untuk flow sensor 
void speedrpm ()
{
  TURBINE++;
}
//mengautur variable ds18b20
const int oneWireBusPin = 4;
OneWire oneWire(oneWireBusPin);
DallasTemperature Sensor(&oneWire);

void setup() {
  // put your setup code here, to run once:
  pinMode(Hsensor, INPUT);
Serial.begin(9600);
Sensor.begin();
attachInterrupt(00, speedrpm, RISING);
SPI.begin();
    Serial.println("CLEARSHEET");
    Serial.println("LABEL,waktu,flow,suhu");


}

void loop() {
  // put your main code here, to run repeatedly:
  // konfigurasi sensor flowmeter untuk mengukur aliran air
  TURBINE = 00; // data awal
  sei(); 
  delay(1000);
  cli();
  Calc = (TURBINE * 60/ 7.5);

  //satuan FLOW RATE Benda cair yaitu L / Hour
  Serial.print(Calc, DEC); // menampilkan hasil pembacaan
  Serial.print(",");

  //konfigurasi sensor ds18b02 untuk mengukur temperatur 
  Sensor.requestTemperatures();
  float celsius = Sensor.getTempCByIndex(0);
  float Farenhait = Sensor.toFahrenheit(celsius);
  //menampilkan ke dalam serial
  
  Serial.print(celsius);
  Serial.println(",");
}
