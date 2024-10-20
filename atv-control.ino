#ifndef MESSAGE_QUEUE_CAPACITY
#define MESSAGE_QUEUE_CAPACITY 3
#endif

#ifndef SESSION_MANAGER_DID_START_SESSION_MESSAGE_TYPE
#define SESSION_MANAGER_DID_START_SESSION_MESSAGE_TYPE 0
#endif

#ifndef SESSION_MANAGER_DID_ALERT_MESSAGE_TYPE
#define SESSION_MANAGER_DID_ALERT_MESSAGE_TYPE 1
#endif

#ifndef SESSION_MANAGER_DID_STOP_SESSION_MESSAGE_TYPE
#define SESSION_MANAGER_DID_STOP_SESSION_MESSAGE_TYPE 2
#endif

#ifndef SESSION_MANAGER_DID_FORCE_STOP_SESSION_MESSAGE_TYPE
#define SESSION_MANAGER_DID_FORCE_STOP_SESSION_MESSAGE_TYPE 3
#endif

#ifndef SAFETY_MODULE_DID_TURN_ON_ALERT_MESSAGE_TYPE
#define SAFETY_MODULE_DID_TURN_ON_ALERT_MESSAGE_TYPE 4
#endif

#ifndef SAFETY_MODULE_DID_TURN_OFF_ALERT_MESSAGE_TYPE
#define SAFETY_MODULE_DID_TURN_OFF_ALERT_MESSAGE_TYPE 5
#endif





#ifndef SESSION_MANAGER_SESSION_STORAGE_ADDRESS
#define SESSION_MANAGER_SESSION_STORAGE_ADDRESS 0
#endif





#ifndef START_SESSION_DIGITAL_PIN
#define START_SESSION_DIGITAL_PIN 4
#endif

#ifndef FORCE_STOP_SESSION_DIGITAL_PIN
#define FORCE_STOP_SESSION_DIGITAL_PIN 5
#endif

#ifndef DISPLAY_NUMBER_OF_SESSIONS_DIGITAL_PIN
#define DISPLAY_NUMBER_OF_SESSIONS_DIGITAL_PIN 6
#endif

#ifndef RESET_SESSION_COUNTER_DIGITAL_PIN
#define RESET_SESSION_COUNTER_DIGITAL_PIN 7
#endif

#ifndef TURN_OFF_DISPLAY_SCREEN_DIGITAL_PIN
#define TURN_OFF_DISPLAY_SCREEN_DIGITAL_PIN 8
#endif

#ifndef DEVICE_POWER_DIGITAL_PIN
#define DEVICE_POWER_DIGITAL_PIN 9
#endif

#ifndef ALERT_DIGITAL_PIN
#define ALERT_DIGITAL_PIN LED_BUILTIN
#endif

#import "serial-user-input-reader.hpp"
#import "digital-user-input-reader.hpp"
#import "digital-switch.hpp"
#import "lcd-i2c-display-screen.hpp"
#import "application.hpp"
#import "logger.hpp"

class ConstantSessionManagerConfiguration: public SessionManagerConfiguration {
public:
  ConstantSessionManagerConfiguration() {}

  uint32_t SessionDuration() const override {
    return (uint32_t)30000;
  }

  uint32_t AlertDuration() const override {
    return (uint32_t)10000;
  }
};

DigitalSwitch devicePowerSwitch(DEVICE_POWER_DIGITAL_PIN);
DigitalSwitch alertSwitch(ALERT_DIGITAL_PIN);
LcdI2CDisplayScreen displayScreen;
ConstantSessionManagerConfiguration sessionManagerConfiguration;
DigitalUserInputReader userInputReader;
// Logger logger;

Application application(&devicePowerSwitch, &alertSwitch, &displayScreen, &sessionManagerConfiguration, &userInputReader, NULL);

void setup() {
  application.Initialize();
}

void loop() {
  application.Loop();
}
