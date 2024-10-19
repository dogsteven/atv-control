#ifndef SWITCH_HEADER
#define SWITCH_HEADER

class Switch {
public:
  virtual bool IsClosed() const = 0;
  virtual void Close() = 0;
  virtual void Open() = 0;
};

#endif