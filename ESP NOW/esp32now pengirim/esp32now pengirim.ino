#include <WiFi.h>
#include <esp_now.h>

// mac address tujuan
uint8_t mac_addr_tujuan[] = {0xAC, 0x0B, 0xFB, 0xCF, 0x4E, 0x40};

// struktur data yang diterima
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
struct_message data_ku;

// variabel untuk jeda kirim
unsigned long waktu_sebelum, interval=2000;

// variabel peerInfo
esp_now_peer_info_t peerInfo;

// callback Jika data terkirim
void cb_terkirim(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nStatus Pengiriman: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sukses" : "Gagal");
}
 
void setup() {
  Serial.begin(115200);

  // mengatur esp ke mode station
  WiFi.mode(WIFI_STA);

  // inisialisasi espnow
  if (esp_now_init() != ESP_OK) {
    Serial.println("Gagal Inisialisasi espnow");
    return;
  }

  // mendaftarkan fungsi callback  
  esp_now_register_send_cb(cb_terkirim);
  
  // Mendata Peer / Kawan
  memcpy(peerInfo.peer_addr, mac_addr_tujuan, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Menambahkan Peer / Kawan
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Gagal Menambah Peer");
    return;
  }
}
 
void loop() {
  if ((millis() - waktu_sebelum) > interval) {    
    // mengisi nilai ke variabel
    strcpy(data_ku.a, "Dari ESP32");
    data_ku.b = random(1, 10);
    data_ku.c = 3.14;
    data_ku.d = true;
  
    // Mengirim Data
    esp_now_send(mac_addr_tujuan, (uint8_t *) &data_ku, sizeof(data_ku));
  
    // update waktu_sebelum
    waktu_sebelum = millis();
  }
}