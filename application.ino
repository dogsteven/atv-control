#import "application.hpp"

Application::Application(UserInputReader* const userInputReader):
  devicePowerSwitch(DEVICE_POWER_DIGITAL_PIN),
  alertSwitch(ALERT_DIGITAL_PIN),
  displayScreen(),
  jobScheduler(),
  messageQueue(),
  persistentStorage(),
  sessionManager(&sessionManagerConfiguration, &jobScheduler, &messageQueue, &persistentStorage),
  safetyModule(&messageQueue),
  alertSystem(&alertSwitch),
  devicePowerController(&devicePowerSwitch),
  userInputReader(userInputReader),
  logger() {}

void Application::Initialize() {
  this->devicePowerSwitch.Initialize();
  this->alertSwitch.Initialize();
  this->displayScreen.Initialize();
  this->sessionManager.Initialize();

  this->messageQueue.AddSubscriber(&(this->alertSystem));
  this->messageQueue.AddSubscriber(&(this->devicePowerController));
  this->messageQueue.AddSubscriber(&(this->logger));
}

void Application::Loop() {
  this->jobScheduler.Tick();

  const UserInput input = this->userInputReader->ReadUserInput();

  if (input == USER_INPUT_START_SESSION) {
    this->startSession();
  } else if (input == USER_INPUT_FORCE_STOP_SESSION) {
    this->forceStopSession();
  } else if (input == USER_INPUT_DISPLAY_NUMBER_OF_SESSIONS) {
    this->displayNumberOfSessions();
  } else if (input == USER_INPUT_RESET_SESSION_COUNTER) {
    this->resetSessionCounter();
  } else if (input == USER_INPUT_TURN_OFF_DISPLAY_SCREEN) {
    this->turnOfDisplayScreen();
  }
}

void Application::startSession() {
  this->sessionManager.StartSession();
}

void Application::forceStopSession() {
  this->sessionManager.ForceStopSession();
}

void Application::displayNumberOfSessions() {
  this->displayScreen.DisplayOn();
  this->displayScreen.Clear();
  this->displayScreen.Print("SO LAN CHOI:");
  this->displayScreen.SetCursor(1, 0);
  this->displayScreen.Print(String(this->sessionManager.NumberOfSessions()));
}

void Application::resetSessionCounter() {
  this->sessionManager.ResetSessionCounter();
  this->displayNumberOfSessions();
}

void Application::turnOfDisplayScreen() {
  this->displayScreen.DisplayOff();
}
