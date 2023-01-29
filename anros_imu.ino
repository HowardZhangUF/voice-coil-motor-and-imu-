#include "imu_data_decode.h"
#include "packet.h"
#include<Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
uint32_t old_frame_ctr = 0;

double p1 = -0.0006562;
double p2 = 0.03382;
double p3 = -0.8398;
double p4 = 10.4;
double p5 = 164.9;
double f = 5;
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  //LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();        
  lcd.setCursor(0,0);
  
  imu_data_decode_init();
}

void loop() {
  /*--------馬達程式--------------*/
  Serial2.println("en");   //對 TX 送出字元 en
  Serial2.println("PFB");
  int x = Serial2.read();
  double kt = p1*pow( x, 4 ) + p2*pow( x, 3 ) + p3*pow( x, 2 ) + p4*x + p5;//using pow instead ^
  double A = f/kt/0.2;
  char B[10];
  dtostrf(A,6,3, B);
  String force = String("t") + B;
  Serial2.println(force);
  Serial.println(Serial2.read());
  Serial2.println("MOVEINC {3} {50}");
  
  /*----------imu程式----------*/
  while (Serial3.available()) {
    char c = Serial3.read();
    packet_decode(c);
  }


  if (frame_count > old_frame_ctr) {
    old_frame_ctr = frame_count;
    if (receive_gwsol.tag != KItemGWSOL) {
     /* Serial.println(F("\t三軸:"));
      Serial.print(receive_imusol.eul[0]);
      Serial.print(',');
      Serial.print(receive_imusol.eul[1]);
      Serial.print(',');
      Serial.println(receive_imusol.eul[2]);*/
      //Serial.println("time per data:");
      //Serial.println(millis());


      //LCD顯示
      lcd.setCursor(0, 0);
      lcd.print(F("X:"));
      lcd.print(receive_imusol.eul[0]);

      lcd.setCursor(8, 0);
      lcd.print(F("Y:"));
      lcd.print(receive_imusol.eul[1]);

      lcd.setCursor(0, 1);
      lcd.print(F("Z:"));
      lcd.print(receive_imusol.eul[2]);      

      lcd.setCursor(12,1);
      lcd.print(F("axis"));
;    }
  }
  
}
