#include <SPI.h>
#include <SD.h>

File myFile;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

 Serial.println("Buka file di kartu sdcard");

 if(!SD.begin(4)){
   Serial.println("Gagal baca microSD!");
   return;
 }
Serial.println("sukses baca microsd");
myFile = SD.open("coba.txt",FILE_WRITE);
if(myFile){
Serial.println("mencoba nulis data di file coba.txt");
myFile.println("success write dataa bossss");
myFile.println("bagaimana hasilnya");
myFile.println("bisakann!!!!!!!!!!");
myFile.close();
Serial.println("SELESAI!");
 }else{
   Serial.println("gagal tulis coba.txt");
 }
}

void loop() {
  // put your main code here, to run repeatedly:

}
