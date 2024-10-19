#import "serial-user-input-reader.hpp"

SerialUserInputReader::SerialUserInputReader() {}

UserInput SerialUserInputReader::ReadUserInput() const {
  if (Serial.available() > 0) {
    const int command = char(Serial.read());

    if (command == 'Q') {
      return USER_INPUT_START_SESSION;
    } else if (command == 'W') {
      return USER_INPUT_FORCE_STOP_SESSION;
    } else if (command == 'E') {
      return USER_INPUT_DISPLAY_NUMBER_OF_SESSIONS;
    } else if (command == 'R') {
      return USER_INPUT_RESET_SESSION_COUNTER;
    } else if (command == 'T') {
      return USER_INPUT_TURN_OFF_DISPLAY_SCREEN;
    }
  }

  return USER_INPUT_NOTHING;
}