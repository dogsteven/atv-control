#ifndef DIGITAL_SWITCH_HEADER
#define DIGITAL_SWITCH_HEADER

#import "switch.hpp"

class DigitalSwitch: public Switch {
private:
  uint8_t const pin;
  bool isLogicallyClosed;

public:
  DigitalSwitch(uint8_t const pin);

  void Initialize() const;

  bool IsClosed() const override;
  void Close() override;
  void Open() override;
};

#endif