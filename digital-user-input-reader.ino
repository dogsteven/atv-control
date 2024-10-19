#import "digital-user-input-reader.hpp"

DigitalUserInputReader::DigitalUserInputReader() {}

void DigitalUserInputReader::Initialize() {
  pinMode(START_SESSION_DIGITAL_PIN, INPUT_PULLUP);
  pinMode(FORCE_STOP_SESSION_DIGITAL_PIN, INPUT_PULLUP);
  pinMode(DISPLAY_NUMBER_OF_SESSIONS_DIGITAL_PIN, INPUT_PULLUP);
  pinMode(RESET_SESSION_COUNTER_DIGITAL_PIN, INPUT_PULLUP);
  pinMode(TURN_OFF_DISPLAY_SCREEN_DIGITAL_PIN, INPUT_PULLUP);
}

UserInput DigitalUserInputReader::ReadUserInput() const {
  if (digitalRead(START_SESSION_DIGITAL_PIN) == LOW) {
    return USER_INPUT_START_SESSION;
  } else if (digitalRead(FORCE_STOP_SESSION_DIGITAL_PIN) == LOW) {
    return USER_INPUT_FORCE_STOP_SESSION;
  } else if (digitalRead(DISPLAY_NUMBER_OF_SESSIONS_DIGITAL_PIN) == LOW) {
    return USER_INPUT_DISPLAY_NUMBER_OF_SESSIONS;
  } else if (digitalRead(RESET_SESSION_COUNTER_DIGITAL_PIN) == LOW) {
    return USER_INPUT_RESET_SESSION_COUNTER;
  } else if (digitalRead(TURN_OFF_DISPLAY_SCREEN_DIGITAL_PIN) == LOW) {
    return USER_INPUT_TURN_OFF_DISPLAY_SCREEN;
  }
  
  return USER_INPUT_NOTHING;
}