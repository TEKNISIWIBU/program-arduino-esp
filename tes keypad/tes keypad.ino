#include<Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS]={
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
//pin yang digunakan untuk
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
//insial libray dan configurasi keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins,colPins,ROWS,COLS);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digunakan untuk menyimpan huruf yang berasala dfari keypad
  //dengan menggunakan(getKey)untuk mengambil karakter 
char customKey = customKeypad.getKey();
//perinta yang digunakan untuk menampilkan karakter
if(customKey){
Serial.println(customKey);
 }
 switch(customKey){
   case 'A':
    Serial.println("ini huruf A");
   break;
   case 'B':
    Serial.println("ini huruf B");
   break;
   case 'C':
    Serial.println("ini huruf C");
   break;
   case 'D':
    Serial.println("ini huruf D");
   break;
   default:
   break;
 }

}
