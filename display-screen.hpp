#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

class DisplayScreen {
public:
  virtual void Initialize() = 0;
  virtual void Clear() = 0;
  virtual void DisplayOn() = 0;
  virtual void DisplayOff() = 0;
  virtual void SetCursor(uint8_t const row, uint8_t const column) = 0;
  virtual void Print(const String& content) = 0;
  virtual void PrintLn(const String& content) = 0;
};

#endif