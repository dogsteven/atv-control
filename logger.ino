#import "logger.hpp"

Logger::Logger() {}

void Logger::OnMessage(const uint8_t messageType, void *const payload) {
  if (messageType == SESSION_MANAGER_DID_START_SESSION_MESSAGE_TYPE) {
    Serial.println("SessionManager did StartSession");
  } else if (messageType == SESSION_MANAGER_DID_ALERT_MESSAGE_TYPE) {
    Serial.println("SessionManager did Alert");
  } else if (messageType == SESSION_MANAGER_DID_STOP_SESSION_MESSAGE_TYPE) {
    Serial.println("SessionManager did StopSession");
  } else if (messageType == SESSION_MANAGER_DID_FORCE_STOP_SESSION_MESSAGE_TYPE) {
    Serial.println("SessionManager did ForceStopSession");
  } else if (messageType == SAFETY_MODULE_DID_TURN_ON_ALERT) {
    Serial.println("SafetyModule did TurnOnAlert");
  } else if (messageType == SAFETY_MODULE_DID_TURN_ON_ALERT) {
    Serial.println("SafetyModule did TurnOffAlert");
  }
}