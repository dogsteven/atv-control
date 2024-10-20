#import "application.hpp"

Application::Application(
  Switch* const devicePowerSwitch,
    Switch* const alertSwitch,
    DisplayScreen* const displayScreen,
    SessionManagerConfiguration* const sessionManagerConfiguration,
    UserInputReader* const userInputReader,
    Logger* const logger
): devicePowerSwitch(devicePowerSwitch),
  alertSwitch(alertSwitch),
  displayScreen(displayScreen),
  sessionManagerConfiguration(sessionManagerConfiguration),
  userInputReader(userInputReader),
  messageQueue(),
  jobScheduler(),
  persistentStorage(),
  sessionManager(sessionManagerConfiguration, &jobScheduler, &messageQueue, &persistentStorage),
  safetyModule(&messageQueue),
  devicePowerController(devicePowerSwitch),
  alertSystem(alertSwitch),
  logger(logger) {}

void Application::Initialize() {
  this->devicePowerSwitch->Initialize();
  this->alertSwitch->Initialize();
  this->displayScreen->Initialize();
  this->userInputReader->Initialize();

  this->sessionManager.Initialize();
  this->safetyModule.Initialize();

  this->messageQueue.AddSubscriber(&(this->alertSystem));
  this->messageQueue.AddSubscriber(&(this->devicePowerController));

  if (this->logger != NULL) {
    this->messageQueue.AddSubscriber(this->logger);
  }
}

void Application::Loop() {
  this->jobScheduler.Tick();

  this->safetyModule.CheckSafety();

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
  this->displayScreen->DisplayOn();
  this->displayScreen->Clear();
  this->displayScreen->Print("SO LAN CHOI:");
  this->displayScreen->SetCursor(1, 0);
  this->displayScreen->Print(String(this->sessionManager.NumberOfSessions()));
}

void Application::resetSessionCounter() {
  this->sessionManager.ResetSessionCounter();
  this->displayNumberOfSessions();
}

void Application::turnOfDisplayScreen() {
  this->displayScreen->DisplayOff();
}
