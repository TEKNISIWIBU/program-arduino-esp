
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9          
#define SS_PIN   10           // PIN SD DAN NSS
String idtag = "" ;
String validUID =  "f3a9583e";
const int led1 = 2;
const int led2 = 4;
const int bell = 3;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Pembuatan objek pustaka rfid

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
Serial.println("akses rumah dengan rfid");
}

void loop() {
// put your main code here, to run repeatedly:
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(bell,OUTPUT);
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
if (validUID == idtag){
  ditemukan = true; 
}
if (ditemukan){
  Serial.println("diterima,okairinasai gosujin-sama");
  digitalWrite(led1,HIGH);
  delay(2000);
  digitalWrite(led1,LOW);
  digitalWrite(bell,HIGH);
  delay(2000);
  digitalWrite(bell,LOW);
}else{
  Serial.println("ditolak,gomenasi gosujin");
  digitalWrite(led1,LOW);
  delay(2000);
  digitalWrite(bell,HIGH);
  delay(2000);
  digitalWrite(bell,LOW);
  
}
//ubah status kartu active ke status halt 
mfrc522.PICC_HaltA();
}
