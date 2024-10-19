#import "push-only-array.hpp"

template<uint8_t Capacity, typename Element>
PushOnlyArray<Capacity, Element>::PushOnlyArray(): size(0) {}

template<uint8_t Capacity, typename Element>
uint8_t PushOnlyArray<Capacity, Element>::Size() const {
  return this->size;
}

template<uint8_t Capacity, typename Element>
Element PushOnlyArray<Capacity, Element>::Read(const uint8_t index) const {
  return this->elements[index];
}

template<uint8_t Capacity, typename Element>
void PushOnlyArray<Capacity, Element>::Push(const Element value) {
  if (this->size >= Capacity) {
    return;
  }

  this->elements[this->size++] = value;
}