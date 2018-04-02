#include <U8g2lib.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
}
void loop()
{
  u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);
  u8g2.setFontDirection(0);
  u8g2.firstPage();
  do {
    /* all graphics commands have to appear within the loop body. */
    u8g2.setCursor(0, 15);
    u8g2.print("Hello World!");
  } while ( u8g2.nextPage() );  
}
