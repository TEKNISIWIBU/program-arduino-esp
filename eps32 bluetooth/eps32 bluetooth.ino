#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESPtest");  //Nama Bluetooth
  Serial.println("bluetooth sudah bisa digunakan!");
}
void loop() {
  // put your main code here, to run repeatedly:
  if (SerialBT.available()) {
    int data_terima = SerialBT.read();
    Serial.write(data_terima);
    SerialBT.write(data_terima);
    if(data_terima == 'R'){
      Serial.println("menyala abangku");
    }
  }
}