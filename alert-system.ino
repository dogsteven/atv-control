#import "alert-system.hpp"

AlertSystem::AlertSystem(Switch* const alertSwitch): alertSwitch(alertSwitch), isAboutToEndSession(false), isSafe(true) {}

void AlertSystem::makeDecision() {
  if (!this->isSafe || this->isAboutToEndSession) {
    this->alertSwitch->Close();
  } else {
    this->alertSwitch->Open();
  }
}

void AlertSystem::OnMessage(const uint8_t messageType, void *const payload) {
  if (messageType == SESSION_MANAGER_DID_ALERT_MESSAGE_TYPE) {
    this->onSessionManagerDidAlert();
  } else if (messageType == SESSION_MANAGER_DID_STOP_SESSION_MESSAGE_TYPE || messageType == SESSION_MANAGER_DID_FORCE_STOP_SESSION_MESSAGE_TYPE) {
    this->onSessionManagerDidEndSession();
  } else if (messageType == SAFETY_MODULE_DID_TURN_ON_ALERT_MESSAGE_TYPE) {
    this->onSafetyModuleDidTurnOnAlert();
  } else if (messageType == SAFETY_MODULE_DID_TURN_OFF_ALERT_MESSAGE_TYPE) {
    this->onSafetyModuleDidTurnOffAlert();
  }
}

void AlertSystem::onSessionManagerDidAlert() {
  this->isAboutToEndSession = true;
  this->makeDecision();
}

void AlertSystem::onSessionManagerDidEndSession() {
  this->isAboutToEndSession = false;
  this->makeDecision();
}

void AlertSystem::onSafetyModuleDidTurnOnAlert() {
  this->isSafe = false;
  this->makeDecision();
}

void AlertSystem::onSafetyModuleDidTurnOffAlert() {
  this->isSafe = true;
  this->makeDecision();
}