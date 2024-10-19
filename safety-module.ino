#import "safety-module.hpp"

SafetyModule::SafetyModule(MessageQueue* const messageQueue): messageQueue(messageQueue), isAlertOn(false) {}

void SafetyModule::collectParameters() {}

bool SafetyModule::calculateSafetyFactor() {
  return true;
}

void SafetyModule::turnOnAlert() {
  if (this->isAlertOn) {
    return;
  }

  this->isAlertOn = true;

  this->messageQueue->PublishMessage(SAFETY_MODULE_DID_TURN_ON_ALERT, NULL);
}

void SafetyModule::turnOffAlert() {
  if (!this->isAlertOn) {
    return;
  }

  this->isAlertOn = false;

  this->messageQueue->PublishMessage(SAFETY_MODULE_DID_TURN_OFF_ALERT, NULL);
}

void SafetyModule::CheckSafety() {
  this->collectParameters();
  ;

  if (this->calculateSafetyFactor()) {
    this->turnOffAlert();
  } else {
    this->turnOnAlert();
  }
}