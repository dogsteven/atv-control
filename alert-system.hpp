#ifndef ALERT_SYSTEM_HEADER
#define ALERT_SYSTEM_HEADER

#import "message-queue.hpp"
#import "session-manager.hpp"
#import "safety-module.hpp"
#import "switch.hpp"

class AlertSystem: public MessageQueueSubscriber {
private:
  Switch* const alertSwitch;

  bool isAboutToEndSession;
  bool isSafe;

  void onSessionManagerDidAlert();
  void onSessionManagerDidEndSession();
  void onSafetyModuleDidTurnOnAlert();
  void onSafetyModuleDidTurnOffAlert();

  void makeDecision();

public:
  AlertSystem(Switch* const alertSwitch);

  void OnMessage(uint8_t const messageType, void* const payload) override;
};

#endif