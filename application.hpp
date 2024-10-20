#include "display-screen.hpp"
#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#import "switch.hpp"
#import "display-screen.hpp"
#import "persistent-storage.hpp"
#import "safety-module.hpp"
#import "alert-system.hpp"
#import "session-manager.hpp"
#import "message-queue.hpp"
#import "job-scheduler.hpp"
#import "user-input-reader.hpp"
#import "device-power-controller.hpp"
#import "logger.hpp"

#ifndef DEVICE_POWER_DIGITAL_PIN
#define DEVICE_POWER_DIGITAL_PIN 12
#endif

#ifndef ALERT_DIGITAL_PIN
#define ALERT_DIGITAL_PIN 13
#endif

class Application {
private:
  Switch* const devicePowerSwitch;
  Switch* const alertSwitch;
  DisplayScreen* const displayScreen;

  SessionManagerConfiguration* const sessionManagerConfiguration;

  UserInputReader* const userInputReader;

  MessageQueue messageQueue;

  JobScheduler jobScheduler;
  PersistentStorage persistentStorage;

  SessionManager sessionManager;
  SafetyModule safetyModule;

  DevicePowerController devicePowerController;
  AlertSystem alertSystem;
  
  Logger* const logger;

  void startSession();
  void forceStopSession();
  void displayNumberOfSessions();
  void resetSessionCounter();
  void turnOfDisplayScreen();

public:
  Application(
    Switch* const devicePowerSwitch,
    Switch* const alertSwitch,
    DisplayScreen* const displayScreen,
    SessionManagerConfiguration* const sessionManagerConfiguration,
    UserInputReader* const userInputReader,
    Logger* const logger
  );

  void Initialize();
  void Loop();
};

#endif