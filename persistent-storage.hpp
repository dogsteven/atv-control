#ifndef PERSISTENT_STORAGE_HEADER
#define PERSISTENT_STORAGE_HEADER

class PersistentStorage {
public:
  PersistentStorage();

  uint32_t readUInt32(uint8_t const address) const;
  void writeUInt32(uint8_t const address, uint32_t const value) const;
};

#endif