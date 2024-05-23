#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int led1 = 5;
const int led2 = 18;
const int led3 = 19;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESPzadid");  //Nama Bluetooth
  Serial.println("bluetooth siap digunakan!");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  //memerikasa data / menerima data yang di dapat dari bluetooth
  /*if(SerialBT.available()){
    Serial.write(SerialBT.read());
  }*/
  //mengirim data dari esp ke pc atau hp
  /*if(Serial.available()){
   SerialBT.write(Serial.read());
  }*/
  if (SerialBT.available()) {
    int data_terima = SerialBT.read();
    Serial.write(data_terima);
    SerialBT.write(data_terima);
    if (data_terima == 'R') {
      Serial.println("led merah menyala");
      digitalWrite(led1, HIGH);
    }
    if (data_terima == 'B') {
      Serial.println("led biru menyala");
      digitalWrite(led2, HIGH);
    }
    if (data_terima == 'H') {
      Serial.println("led hijau menyala");
      digitalWrite(led3, HIGH);
    }
    if (data_terima == 'M') {
      Serial.println("semua led mati");
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
     if (data_terima == 'S') {
      Serial.println("semua led menyala");
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
  }
}