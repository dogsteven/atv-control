#ifndef PUSH_ONLY_ARRAY_HEADER
#define PUSH_ONLY_ARRAY_HEADER

template<uint8_t Capacity, typename Element>
class PushOnlyArray {
private:
  Element elements[Capacity];
  uint8_t size;

public:
  PushOnlyArray();

  uint8_t Size() const;
  Element Read(uint8_t const index) const;

  void Push(Element const value);
};

#endif