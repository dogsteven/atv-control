#ifndef SAFETY_MODULE_HEADER
#define SAFETY_MODULE_HEADER

#import "message-queue.hpp"

#ifndef SAFETY_MODULE_DID_TURN_ON_ALERT
#define SAFETY_MODULE_DID_TURN_ON_ALERT 0
#endif

#ifndef SAFETY_MODULE_DID_TURN_OFF_ALERT
#define SAFETY_MODULE_DID_TURN_OFF_ALERT 1
#endif

class SafetyModule {
private:
  MessageQueue* const messageQueue;

  bool isAlertOn;

  void collectParameters();
  bool calculateSafetyFactor();

  void turnOnAlert();
  void turnOffAlert();

public:
  SafetyModule(MessageQueue* const messageQueue);

  void CheckSafety();
};

#endif