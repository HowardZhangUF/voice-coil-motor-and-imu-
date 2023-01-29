#include "imu_data_decode.h"
#include "packet.h"
//#include<Wire.h>
//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x3F, 16, 2);
uint32_t old_frame_ctr = 0;
//unsigned long time_now = 0;

void setup() {
  Serial.begin(115200);
//  Serial2.begin(115200);

 /* //LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();        
  lcd.setCursor(0,0);*/
  
  imu_data_decode_init();
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    packet_decode(c);
    Serial.println(F("\t三軸:"));
  }
  

  if (frame_count > old_frame_ctr) {
    old_frame_ctr = frame_count;
    if (receive_gwsol.tag != KItemGWSOL) {
      Serial.println(F("\t三軸:"));
      Serial.print(receive_imusol.eul[0]);
      Serial.print(',');
      Serial.print(receive_imusol.eul[1]);
      Serial.print(',');
      Serial.println(receive_imusol.eul[2]);
      //time_now = millis()
      //Serial.println("time per data:");
      //Serial.println(time_now);


     /* //LCD顯示
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
      lcd.print(F("axis"));*/
    }
  }
  
}
