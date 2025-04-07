#include <SPI.h>
#include <MFRC522.h>
#include <EEPROMex.h>
// pin yang digunakan rfid
const int PIN_RST = 9;
const int PIN_SS = 10; // Pin SDA atau NSS

char charBuff[15];
String idTag = ""; //

// Pembuatan objek MFRC522 dan keypad
MFRC522 RFID(PIN_SS, PIN_RST);
boolean daftar = false;
boolean hapus = false;
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  RFID.PCD_Init();
  Serial.println("menyimpan data rfid !");
  delay(100);
}

void loop()
{ // variable untuk mendapatkan nilai keypad
  if (Serial.available () > 0)
  {
    char text = Serial.read();
    if (text == '1')
      {
        daftar = true;
      }
    else if (text == '2')
    {
      Serial.print("data tag di eeprom ");
      char output[] = "";
      EEPROM.readBlock<char>(0, output, 15);
      String cstring = String(output);
      Serial.print("UID:");
      Serial.println(output);
     
    }
    else if (text == '3'){
      Serial.print("menghapus data tag");
    }
  }

  // mendaftarkan kartu /tag pada eeprom
  if (daftar == true)
  {
    if (!RFID.PICC_IsNewCardPresent() || !RFID.PICC_ReadCardSerial())
    {
      return;
    }
    idTag = "";
    for (byte i = 0; i < RFID.uid.size; i++)
    {
      idTag += RFID.uid.uidByte[i];
    }
    char charBuff[15];
    idTag.toCharArray(charBuff, 15);
    EEPROM.writeBlock<char>(0, charBuff, 15);
    RFID.PICC_HaltA();
  }
}

