#ifndef DEVICE_POWER_CONTROLLER_HEADER
#define DEVICE_POWER_CONTROLLER_HEADER

#import "message-queue.hpp"
#import "session-manager.hpp"
#import "safety-module.hpp"
#import "switch.hpp"

class DevicePowerController: public MessageQueueSubscriber {
private:
  Switch* const devicePowerSwitch;

  bool deviceIsAllowedToOperate;
  bool isSafe;

  void onSessionManagerDidStartSession();
  void onSessionManagerDidStopSession();
  void onSafetyModuleDidTurnOnAlert();
  void onSafetyModuleDidTurnOffAlert();

  void makeDecision();

public:
  DevicePowerController(Switch* const devicePowerSwitch);

  void OnMessage(uint8_t const messageType, void* const payload) override;
};

#endif