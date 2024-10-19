#import "device-power-controller.hpp"

DevicePowerController::DevicePowerController(
  Switch* const devicePowerSwitch
): devicePowerSwitch(devicePowerSwitch), isSafe(true), deviceIsAllowedToOperate(false) {}

void DevicePowerController::makeDecision() {
  if (this->isSafe && this->deviceIsAllowedToOperate) {
    this->devicePowerSwitch->Close();
  } else {
    this->devicePowerSwitch->Open();
  }
}

void DevicePowerController::OnMessage(const uint8_t messageType, void *const payload) {
  if (messageType == SESSION_MANAGER_DID_START_SESSION_MESSAGE_TYPE) {
    this->onSessionManagerDidStartSession();
  } else if (messageType == SESSION_MANAGER_DID_STOP_SESSION_MESSAGE_TYPE || messageType == SESSION_MANAGER_DID_FORCE_STOP_SESSION_MESSAGE_TYPE) {
    this->onSessionManagerDidStopSession();
  } else if (messageType == SAFETY_MODULE_DID_TURN_ON_ALERT) {
    this->onSafetyModuleDidTurnOnAlert();
  } else if (messageType == SAFETY_MODULE_DID_TURN_OFF_ALERT) {
    this->onSafetyModuleDidTurnOffAlert();
  }
}

void DevicePowerController::onSessionManagerDidStartSession() {
  this->deviceIsAllowedToOperate = true;
  this->makeDecision();
}

void DevicePowerController::onSessionManagerDidStopSession() {
  this->deviceIsAllowedToOperate = false;
  this->makeDecision();
}

void DevicePowerController::onSafetyModuleDidTurnOnAlert() {
  this->isSafe = false;
  this->makeDecision();
}

void DevicePowerController::onSafetyModuleDidTurnOffAlert() {
  this->isSafe = true;
  this->makeDecision();
}