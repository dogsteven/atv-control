#import "digital-switch.hpp"

DigitalSwitch::DigitalSwitch(uint8_t const pin): pin(pin), isLogicallyClosed(false) {}

void DigitalSwitch::Initialize() const {
  pinMode(this->pin, OUTPUT);
}

bool DigitalSwitch::IsClosed() const { 
  return this->isLogicallyClosed;
}

void DigitalSwitch::Close() {
  if (this->isLogicallyClosed) {
    return;
  }

  this->isLogicallyClosed = true;
  digitalWrite(this->pin, HIGH);
}

void DigitalSwitch::Open() {
  if (!this->isLogicallyClosed) {
    return;
  }

  this->isLogicallyClosed = false;
  digitalWrite(this->pin, LOW);
}