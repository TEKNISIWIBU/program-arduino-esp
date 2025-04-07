#include <Keypad.h>

// Konfigurasi keypad
const byte ROWS = 4; // Jumlah baris
const byte COLS = 4; // Jumlah kolom
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Pin untuk baris
byte colPins[COLS] = {5, 4, 3, 2}; // Pin untuk kolom

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int sensorPin = A0; // Pin untuk sensor
const int buzzerPin = 10; // Pin untuk buzzer

int batasAtas = 0; // Batas atas
int batasBawah = 0; // Batas bawah

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  Serial.println("Set batas bawah dengan menekan angka di keypad:");
}

void loop() {
  static bool setBatasBawah = true; // Menentukan apakah sedang set batas bawah
  static String input = ""; // String sementara untuk menyimpan input keypad

  // Membaca input dari keypad
  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') { // Jika tombol angka ditekan
      input += key; // Tambahkan angka ke input
      Serial.print(key);
    } else if (key == '#') { // Tombol '#' untuk konfirmasi input
      if (setBatasBawah) {
        batasBawah = input.toInt(); // Konversi input ke integer
        Serial.println("\nBatas bawah telah diset: " + String(batasBawah));
        Serial.println("Set batas atas dengan menekan angka di keypad:");
        setBatasBawah = false; // Pindah ke set batas atas
      } else {
        batasAtas = input.toInt(); // Konversi input ke integer
        Serial.println("\nBatas atas telah diset: " + String(batasAtas));
        Serial.println("Mulai membaca sensor...");
      }
      input = ""; // Reset input
    } else if (key == '*') { // Tombol '*' untuk reset
      Serial.println("\nReset setpoint.");
      setBatasBawah = true;
      input = "";
      Serial.println("Set batas bawah dengan menekan angka di keypad:");
    }
  }

  // Baca nilai sensor jika batas atas dan bawah telah diset
  if (!setBatasBawah && batasAtas > batasBawah) {
    int nilaiSensor = analogRead(sensorPin);
    nilaiSensor = map(nilaiSensor, 0, 1023, 0, 100); // Mapping nilai sensor (0-100)
    Serial.println("Nilai sensor: " + String(nilaiSensor));

    if (nilaiSensor > batasAtas || nilaiSensor < batasBawah) {
      digitalWrite(buzzerPin, HIGH); // Nyalakan buzzer
    } else {
      digitalWrite(buzzerPin, LOW); // Matikan buzzer
    }

    delay(500); // Delay untuk membaca sensor
  }
}
