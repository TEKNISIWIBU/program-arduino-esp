//fungsi yang digunakan 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
// Deklarasi variabel
int error, sudut_ref, motor_pwm;
double sudut_aktual, p, i, d, nilai_PID, prev_error, integral, derivative;
const int Toleransi = 5;
const double Kp = 0.5, Ki = 0.1, Kd = 0.01;
#define sensor 2
//deklarasi variabel yang digunakan untuk tachometer
unsigned long timeold;
unsigned int rpmku; //variabel tipe data integer
float rpmfix;
int kalibrasi;
volatile int objects;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(8, OUTPUT);  // IN1
  pinMode(9, OUTPUT);  // IN2
  pinMode(10, OUTPUT); // ENA (PWM)
  attachInterrupt(digitalPinToInterrupt(sensor), count, RISING);
  objects = 0;
  rpmku = 0;
  kalibrasi = 0;
  delay(2000);
  pinMode(sensor, INPUT);
  prev_error = 0;
  integral = 0;
}

void loop() {
  // Perhitungan putaran rpm dan perhitungan putaran di setiap hole
  rpmku = 30*1000/(millis()-timeold)*objects;
  timeold = millis();
  objects = 0;

  kalibrasi = (rpmku-150)/109;
  rpmfix = kalibrasi * 10;
  if (rpmfix > 2000) {
  rpmfix = 0;
  }

  // Membaca nilai referensi dari potensiometer
  int set = analogRead(A0);
  sudut_ref = map(set, 0, 1023, 0, 400);  // Ubah sesuai dengan rentang RPM yang diinginkan
  sudut_aktual = rpmfix;
  error = sudut_ref - sudut_aktual;

  if (abs(error) <= Toleransi) error = 0;

  // Kontrol Proposional
  p = Kp * error;

  // Kontrol Integral
  integral += error;
  i = Ki * integral;

  // Kontrol Derivatif
  derivative = error - prev_error;
  d = Kd * derivative;

  // Menghitung nilai PID
  nilai_PID = p + i + d;

  // Menyimpan error sebelumnya untuk perhitungan derivatif
  prev_error = error;

  // Menampilkan nilai pembacaan sensor dan perhitungan rpm
  Serial.print("RPM: ");
  Serial.print(rpmfix);
  Serial.print(",");
  Serial.print(" Set: ");
  Serial.print(sudut_ref);
  Serial.print(",");
  Serial.print(" Error: ");
  Serial.println(error);

  /*
  Serial.print(" PID: ");
  Serial.println(nilai_PID);*/
//menampilkan nya di lcd
    lcd.setCursor(0,0);
    lcd.print("rpm:");
    lcd.print(rpmfix);
    lcd.print("  ");
    lcd.print("ref:");
    lcd.print(sudut_ref);
    lcd.print("  ");

    lcd.setCursor(0,1);
    /*
    lcd.print("Er:");
    lcd.print(error);
    lcd.print("  ");
    */
    lcd.print("PID:");
    lcd.print(nilai_PID);
    lcd.print(" ");
  delay(1000);

  // Mengontrol motor berdasarkan nilai PID
  if (nilai_PID < 0) {
    motor_pwm = constrain(abs(nilai_PID), 1, 255);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    analogWrite(10, motor_pwm);
  } else if (nilai_PID > 0) {
    motor_pwm = constrain(abs(nilai_PID), 1, 255);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    analogWrite(10, motor_pwm);
  } else {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    analogWrite(10, 0);
  }
}

// Fungsi untuk pembacaan interrupt
void count() {
  objects++;
}
