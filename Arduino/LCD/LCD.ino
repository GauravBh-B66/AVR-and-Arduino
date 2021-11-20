#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte smiley[8] = {
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000,
  
};

void setup() {
  lcd.begin(16, 2);  
  
}

void loop() {
  lcd.clear();
  lcd.createChar(0,smiley);
  lcd.write(byte(0));
  }
