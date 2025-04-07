#include<RFID.h>
#include<SPI.h>

#define SDA_PIN 10
#define RST_PIN 9

RFID rfid(SDA_PIN,RST_PIN);

int serNum[5];

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SPI.begin();
rfid.init();
delay(1000);
Serial.println("pembacaan rfid dengan ektp");
Serial.print("tempelkan kartu!");
}

void loop() {
  // put your main code here, to run repeatedly:
if(rfid.isCard()){
 if(rfid.readCardSerial()){
    Serial.print("Kode Tag E-KTP");
      Serial.print(" : ");
      Serial.print(rfid.serNum[0]);
      Serial.print(" ");
      Serial.print(rfid.serNum[1]);
      Serial.print(" ");
      Serial.print(rfid.serNum[2]);
      Serial.print(" ");
      Serial.print(rfid.serNum[3]);
      Serial.print(" ");
      Serial.print(rfid.serNum[4]);
      Serial.println("");
  }
 }
 rfid.halt();
 delay(1000);
}
