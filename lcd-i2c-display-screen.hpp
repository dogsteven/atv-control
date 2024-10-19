#ifndef LCD_I2C_DISPLAY_SCREEN_HEADER
#define LCD_I2C_DISPLAY_SCREEN_HEADER

#import "display-screen.hpp"
#import <LiquidCrystal_I2C.h>

class LcdI2CDisplayScreen: public DisplayScreen {
private:
  LiquidCrystal_I2C lcd;

public:
  LcdI2CDisplayScreen();

  void Initialize() override;
  void Clear() override;
  void DisplayOn() override;
  void DisplayOff() override;
  void SetCursor(uint8_t const row, uint8_t const column) override;
  void Print(const String& content) override;
  void PrintLn(const String& content) override;
};

#endif