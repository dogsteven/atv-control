#ifndef SWITCH_HEADER
#define SWITCH_HEADER

class Switch {
public:
  virtual void Initialize() = 0;
  virtual bool IsClosed() const = 0;
  virtual void Close() = 0;
  virtual void Open() = 0;
};

#endif