#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#import "digital-switch.hpp"
#import "persistent-storage.hpp"
#import "safety-module.hpp"
#import "alert-system.hpp"
#import "session-manager.hpp"
#import "message-queue.hpp"
#import "job-scheduler.hpp"
#import "user-input-reader.hpp"
#import "device-power-controller.hpp"
#import "lcd-i2c-display-screen.hpp"
#import "logger.hpp"

#ifndef DEVICE_POWER_DIGITAL_PIN
#define DEVICE_POWER_DIGITAL_PIN 12
#endif

#ifndef ALERT_DIGITAL_PIN
#define ALERT_DIGITAL_PIN 13
#endif

class ConstantSessionManagerConfiguration: public SessionManagerConfiguration {
public:
  ConstantSessionManagerConfiguration() {}

  uint32_t SessionDuration() const {
    return (uint32_t)30000;
  }

  uint32_t AlertDuration() const {
    return (uint32_t)10000;
  }
};

class Application {
private:
  DigitalSwitch devicePowerSwitch;
  DigitalSwitch alertSwitch;
  LcdI2CDisplayScreen displayScreen;

  ConstantSessionManagerConfiguration sessionManagerConfiguration;

  JobScheduler jobScheduler;
  MessageQueue messageQueue;
  PersistentStorage persistentStorage;

  SessionManager sessionManager;
  SafetyModule safetyModule;

  AlertSystem alertSystem;
  DevicePowerController devicePowerController;

  UserInputReader* const userInputReader;

  Logger logger;

  void startSession();
  void forceStopSession();
  void displayNumberOfSessions();
  void resetSessionCounter();
  void turnOfDisplayScreen();

public:
  Application(UserInputReader* const userInputReader);

  void Initialize();
  void Loop();
};

#endif