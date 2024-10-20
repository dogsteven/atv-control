#import "safety-module.hpp"

SafetyModule::SafetyModule(MessageQueue* const messageQueue): messageQueue(messageQueue), isAlertOn(false) {}

void SafetyModule::Initialize() {
  pinMode(0, INPUT_PULLUP);
}

bool SafetyModule::collectParametersAndCalculateSafety() {
  return digitalRead(0) == HIGH;
}

void SafetyModule::turnOnAlert() {
  if (this->isAlertOn) {
    return;
  }

  this->isAlertOn = true;

  this->messageQueue->PublishMessage(SAFETY_MODULE_DID_TURN_ON_ALERT_MESSAGE_TYPE, NULL);
}

void SafetyModule::turnOffAlert() {
  if (!this->isAlertOn) {
    return;
  }

  this->isAlertOn = false;

  this->messageQueue->PublishMessage(SAFETY_MODULE_DID_TURN_OFF_ALERT_MESSAGE_TYPE, NULL);
}

void SafetyModule::CheckSafety() {
  if (this->collectParametersAndCalculateSafety()) {
    this->turnOffAlert();
  } else {
    this->turnOnAlert();
  }
}