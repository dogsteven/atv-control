#import "lcd-i2c-display-screen.hpp"

LcdI2CDisplayScreen::LcdI2CDisplayScreen(): lcd(0x27, 16, 2) {}

void LcdI2CDisplayScreen::Initialize() {
  this->lcd.begin();
  this->DisplayOff();
}

void LcdI2CDisplayScreen::Clear() {
  this->lcd.clear();
}

void LcdI2CDisplayScreen::DisplayOn() {
  this->lcd.backlight();
  this->lcd.display();
}

void LcdI2CDisplayScreen::DisplayOff() {
  this->lcd.noDisplay();
  this->lcd.noBacklight();
}

void LcdI2CDisplayScreen::SetCursor(uint8_t const row, uint8_t const column) {
  this->lcd.setCursor(column, row);
}

void LcdI2CDisplayScreen::Print(const String& content) {
  this->lcd.print(content);
}

void LcdI2CDisplayScreen::PrintLn(const String &content) {
  this->lcd.println(content);
}