#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  // put your setup code here, to run once:
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  Serial.println();
  Serial.println("memulai DFplayer.....");

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin: ");
    Serial.println("1.cek ulang koneksi");
    Serial.println("2.masukkan microSD!");
    while(true);
  }
  Serial.println("mp3 aktif.");

  myDFPlayer.volume(30);
  myDFPlayer.play(2);
}

void loop() {
  // put your main code here, to run repeatedly:
}