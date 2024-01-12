#include "TimeLib.h"
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 time_t waktu = now();
 tampilkanWaktu(waktu);
 delay(1000);
}
void tampilkanWaktu(time_t waktu){
 int tg = day(waktu);
 int bl = month(waktu);
 int th = year(waktu);
 int jam = hour(waktu);
 int menit = minute(waktu);
 int detik = second(waktu);

 Serial.print(tg);
 Serial.print("/");
 Serial.print(bl);
 Serial.print("/");
 Serial.print(th);

 Serial.print(" ");
 
 tampil2digit(jam);
 Serial.print(':');
 tampil2digit(menit);
 Serial.print(':');
 tampil2digit(detik);
 Serial.println();
}
void tampil2digit(int bil){
 if(bil < 10 && bil >=0){
   Serial.print('0');
 }
 Serial.print(bil);
}