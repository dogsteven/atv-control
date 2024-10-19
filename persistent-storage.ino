#import "persistent-storage.hpp"
#import <EEPROM.h>

PersistentStorage::PersistentStorage() {}

uint32_t PersistentStorage::readUInt32(const uint8_t address) const {
  uint32_t result = 0;

  for (uint8_t i = 0; i < 4; ++i) {
    result += EEPROM.read(address + i) << (8 * (3 - i));
  }

  return result;
}

void PersistentStorage::writeUInt32(const uint8_t address, const uint32_t value) const {
  for (uint8_t i = 0; i < 4; ++i) {
    EEPROM.write(address + i, (value << (8 * i)) >> 24);
    if (i < 3) delay(5);
  }
}