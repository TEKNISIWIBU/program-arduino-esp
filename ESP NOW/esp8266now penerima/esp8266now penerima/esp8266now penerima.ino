#include <ESP8266WiFi.h>
#include <espnow.h>

// struktur data yang diterima
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
struct_message data_ku;

// callback jika menerima data
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&data_ku, incomingData, sizeof(data_ku));
  Serial.print("Bytes Diterima: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(data_ku.a);
  Serial.print("Int: ");
  Serial.println(data_ku.b);
  Serial.print("Float: ");
  Serial.println(data_ku.c);
  Serial.print("Bool: ");
  Serial.println(data_ku.d);
  Serial.println();
}
 
void setup() {
  Serial.begin(115200);
  
  // mengatur esp ke mode station
  WiFi.mode(WIFI_STA);

  // inisialisasi espnow
  if (esp_now_init() != 0) {
    Serial.println("Gagal Inisialisasi espnow");
    return;
  }
  
  // mendaftarkan fungsi callback
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  
}