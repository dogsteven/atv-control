#ifndef DIGITAL_USER_INPUT_READER_HEADER
#define DIGITAL_USER_INPUT_READER_HEADER

#ifndef START_SESSION_DIGITAL_PIN
#define START_SESSION_DIGITAL_PIN 4
#endif

#ifndef FORCE_STOP_SESSION_DIGITAL_PIN
#define FORCE_STOP_SESSION_DIGITAL_PIN 5
#endif

#ifndef DISPLAY_NUMBER_OF_SESSIONS_DIGITAL_PIN
#define DISPLAY_NUMBER_OF_SESSIONS_DIGITAL_PIN 6
#endif

#ifndef RESET_SESSION_COUNTER_DIGITAL_PIN
#define RESET_SESSION_COUNTER_DIGITAL_PIN 7
#endif

#ifndef TURN_OFF_DISPLAY_SCREEN_DIGITAL_PIN
#define TURN_OFF_DISPLAY_SCREEN_DIGITAL_PIN 8
#endif

#import "user-input-reader.hpp"

class DigitalUserInputReader: public UserInputReader {
public:
  DigitalUserInputReader();

  void Initialize() override;

  UserInput ReadUserInput() const override;
};

#endif