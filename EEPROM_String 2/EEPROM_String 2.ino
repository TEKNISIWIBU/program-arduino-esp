#include <EEPROM.h>
String data_simpan, data_baca;  //menampung nilai string atau kata
byte panjang_data, panjang_baca;
byte alamat_panjang = 0, alamat_data = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  data_simpan = "HAI, TEKNISI WIBU";
  panjang_data = data_simpan.length();  // menyimpan nilai panjang string
  Serial.print(data_simpan);
  Serial.print(" ");
  Serial.print(panjang_data);
  Serial.println(" ");
  EEPROM.update(alamat_panjang, panjang_data);  // memyimpan data string dieeprom dengan alamat dari variabel alamat panjang
  //menampilkan data string dengan menggunakan for dan menampilkan alamat yang digunakan
  //untuk meyimpan setiap karkater string
  /*
  for (int x = 0; x < panjang_data; x++) {
    Serial.print("alamat: ");
    Serial.print(x + alamat_data);
    Serial.print(" - ");
    Serial.println(data_simpan[x]);
    EEPROM.update(x + alamat_data, data_simpan[x]);  //menyimpan data
  }*/
  //membaca panjang atau nilai eeprom yang tersimpan
  panjang_baca = EEPROM.read(alamat_panjang);
  for (int y = 0; y < panjang_baca; y++) {
    data_baca += char(EEPROM.read(y + alamat_data));
  }
  Serial.print("panjang data: ");
  Serial.println(panjang_baca);
  Serial.print("isi eeprom:");
  Serial.println(data_baca);
}

void loop() {
  // put your main code here, to run repeatedly:
}