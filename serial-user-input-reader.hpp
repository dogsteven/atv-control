#ifndef SERIAL_USER_INPUT_READER_HEADER
#define SERIAL_USER_INPUT_READER_HEADER

#import "user-input-reader.hpp"

class SerialUserInputReader: public UserInputReader {
public:
  SerialUserInputReader();

  void Initialize() override;

  UserInput ReadUserInput() const override;
};

#endif