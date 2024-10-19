#import "session-manager.hpp"

#ifndef SESSION_MANAGER_SESSION_STORAGE_ADDRESS
#define SESSION_MANAGER_SESSION_STORAGE_ADDRESS 0
#endif

SessionManager::SessionManager(
  SessionManagerConfiguration* const configuration,
  JobScheduler* const jobScheduler,
  MessageQueue* const messageQueue,
  PersistentStorage* const persistentStorage
): configuration(configuration),
  jobScheduler(jobScheduler),
  messageQueue(messageQueue),
  persistentStorage(persistentStorage),
  state(SESSION_MANAGER_STATE_UNINITIALIZED),
  numberOfSessions(0),
  currentJob(NULL) {}

/** ------ BEGIN PUBLIC GETTERS SECTION ------ **/

SessionManagerState SessionManager::State() const {
  return this->state;
}

uint32_t SessionManager::NumberOfSessions() const {
  return this->numberOfSessions;
}

/** ------ END PUBLIC GETTERS SECTION ------ **/









/** ------ BEGIN SESSION COUNTING SECTION ------ **/

void SessionManager::retrieveNumberOfSessionsFromPersistentStorage() {
  this->numberOfSessions = this->persistentStorage->readUInt32(SESSION_MANAGER_SESSION_STORAGE_ADDRESS);
}

void SessionManager::saveNumberOfSessionsToPersistentStorage() {
  this->persistentStorage->writeUInt32(SESSION_MANAGER_SESSION_STORAGE_ADDRESS, this->numberOfSessions);
}

void SessionManager::increaseNumberOfSessions() {
  ++this->numberOfSessions;
  this->saveNumberOfSessionsToPersistentStorage();
}

void SessionManager::ResetSessionCounter() {
  this->numberOfSessions = 0;
  this->saveNumberOfSessionsToPersistentStorage();
}

/** ------ END SESSION COUNTING SECTION ------ **/










/** ------ BEGIN LIFECYCLE SECTION ------ **/

void SessionManager::Initialize() {
  if (this->state != SESSION_MANAGER_STATE_UNINITIALIZED) {
    return;
  }

  this->retrieveNumberOfSessionsFromPersistentStorage();

  this->state = SESSION_MANAGER_STATE_READY;
}

void SessionManager::StartSession() {
  if (this->state != SESSION_MANAGER_STATE_READY) {
    return;
  }

  this->state = SESSION_MANAGER_STATE_RUNNING;

  this->increaseNumberOfSessions();

  this->currentJob = this->jobScheduler->ScheduleDelay(this->configuration->SessionDuration() - this->configuration->AlertDuration(), SessionManager::dispatchAlert, this);

  this->messageQueue->PublishMessage(SESSION_MANAGER_DID_START_SESSION_MESSAGE_TYPE, NULL);
}

void SessionManager::ForceStopSession() {
  if (this->state == SESSION_MANAGER_STATE_READY || this->state == SESSION_MANAGER_STATE_UNINITIALIZED) {
    return;
  }

  this->state = SESSION_MANAGER_STATE_READY;

  if (this->currentJob != NULL) {
    this->jobScheduler->CancelJob(this->currentJob);
  }

  this->messageQueue->PublishMessage(SESSION_MANAGER_DID_FORCE_STOP_SESSION_MESSAGE_TYPE, NULL);
}

void SessionManager::alert() {
  if (this->state != SESSION_MANAGER_STATE_RUNNING) {
    return;
  }

  this->state = SESSION_MANAGER_STATE_ALERTING;

  this->currentJob = this->jobScheduler->ScheduleDelay(this->configuration->AlertDuration(), SessionManager::dispatchStopSession, this);

  this->messageQueue->PublishMessage(SESSION_MANAGER_DID_ALERT_MESSAGE_TYPE, NULL);
}

void SessionManager::stopSession() {
  if (this->state != SESSION_MANAGER_STATE_ALERTING) {
    return;
  }

  this->state = SESSION_MANAGER_STATE_READY;
  
  this->currentJob = NULL;

  this->messageQueue->PublishMessage(SESSION_MANAGER_DID_STOP_SESSION_MESSAGE_TYPE, NULL);
}

static bool SessionManager::dispatchAlert(SessionManager* const sessionManager) {
  sessionManager->alert();
  return false;
}

static bool SessionManager::dispatchStopSession(SessionManager* const sessionManager) {
  sessionManager->stopSession();
  return false;
}

/** ------ END LIFECYCLE SECTION ------ **/