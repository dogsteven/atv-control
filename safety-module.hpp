#ifndef SAFETY_MODULE_HEADER
#define SAFETY_MODULE_HEADER

#import "message-queue.hpp"

#ifndef SAFETY_MODULE_DID_TURN_ON_ALERT_MESSAGE_TYPE
#define SAFETY_MODULE_DID_TURN_ON_ALERT_MESSAGE_TYPE 0
#endif

#ifndef SAFETY_MODULE_DID_TURN_OFF_ALERT_MESSAGE_TYPE
#define SAFETY_MODULE_DID_TURN_OFF_ALERT_MESSAGE_TYPE 1
#endif

class SafetyModule {
private:
  MessageQueue* const messageQueue;

  bool isAlertOn;

  bool collectParametersAndCalculateSafety();

  void turnOnAlert();
  void turnOffAlert();

public:
  SafetyModule(MessageQueue* const messageQueue);

  void Initialize();

  void CheckSafety();
};

#endif