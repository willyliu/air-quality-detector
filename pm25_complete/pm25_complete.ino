
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
char buf[32] = {0};
int idx = 0; 
int yOffset = 0;
const int kFontHeight = 10;
const int kScreenHeight = 64;
int pm25 = 0;
int spinnerIndex = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);  
  Serial.println("setup()");   
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    buf[idx++] = Serial.read();
  }
  bool isUpdated = false;
  if (buf[0] == 0x42 && buf[1] == 0x4d) {
    pm25 = ( buf[12] << 8 ) | buf[13];
    isUpdated = true;
    spinnerIndex = (spinnerIndex + 1) % 3;
  }
  idx = 0;
  u8g2.firstPage();
  do {
    /* all graphics commands have to appear within the loop body. */
    u8g2.setCursor(0, yOffset + kFontHeight);
    u8g2.print("pm2.5: ");
    u8g2.print(pm25);
    u8g2.print("ug/m3");
    if (isUpdated) {
      u8g2.setCursor(0, yOffset +kFontHeight * 2);
      char spinners[] = {'/', '-', '\\'};
      u8g2.print(spinners[spinnerIndex]);
    }
  } while ( u8g2.nextPage() );  
  delay(100);
}
