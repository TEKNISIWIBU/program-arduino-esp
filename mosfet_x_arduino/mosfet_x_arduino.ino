#define mosfet 6
void setup() {
  // put your setup code here, to run once:
pinMode(mosfet, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for ( int i =  0 ; i < 360 ; i ++ ) { 
    //mengubah sudut 0-360 menjadi radian (diperlukan untuk fungsi sin) 
    float rad = DEG_TO_RAD * i ;
    //hitung sin sudut sebagai angka antara 0 dan 255 
    int sinOut =  constrain ( ( sin ( rad )  * 128 )  + 128 , 0 , 255 ) ; 
    analogWrite ( mosfet, sinOut ) ;
    delay(100) ; 
  }
}
