
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN  9          
#define SS_PIN   10           // PIN SD DAN NSS
const int led1   (2);
const int led2   (4);
const int relay  (3);

String idtag = "" ;
String validUID[2] = {
  "f3a9583e",
  "02520f0e",
};

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Pembuatan objek pustaka rfid
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
// put your setup code here, to run once:
lcd.begin();
lcd.backlight();
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
lcd.setCursor(0,0);
lcd.println("akses rumah rfid");
lcd.setCursor(0,1);
lcd.print("tag rfid....");
}

void loop() {
// put your main code here, to run repeatedly:
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(relay,OUTPUT);
//periksa tag rfid 
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 //peroleh identitas tag 
idtag ="";
for (byte j = 0; j < mfrc522.uid.size; j++) {
  char teksHeksa[3];
  sprintf(teksHeksa,"%02x",mfrc522.uid.uidByte[j]);
  idtag = idtag + teksHeksa;
}
boolean ditemukan = false;
for(byte i = 0; i < 2; i++){
if (validUID[i] == idtag){
  ditemukan = true;
  break; 
 }
}
Serial.print("UID = ");
Serial.println(idtag);

if (ditemukan){
  lcd.println("diterima");
  lcd.print("okarinasai gosujin");
  digitalWrite(led2,HIGH);
  digitalWrite(led1,LOW);
  digitalWrite(relay,HIGH);
  delay(1000);
  digitalWrite(relay,LOW);
}else{
  lcd.println("ditolak,gomenasi gosujin-sama");
  
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(relay,LOW);
}
//ubah status kartu active ke status halt 
mfrc522.PICC_HaltA();
}
