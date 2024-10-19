#ifndef SESSION_MANAGER_HEADER
#define SESSION_MANAGER_HEADER

#import "message-queue.hpp"
#import "job-scheduler.hpp"
#import "persistent-storage.hpp"

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

class SessionManagerConfiguration {
public:
  virtual uint32_t SessionDuration() const;
  virtual uint32_t AlertDuration() const;
};

enum SessionManagerState {
  SESSION_MANAGER_STATE_UNINITIALIZED,
  SESSION_MANAGER_STATE_READY,
  SESSION_MANAGER_STATE_RUNNING,
  SESSION_MANAGER_STATE_ALERTING
};

class SessionManager {
private:
  SessionManagerConfiguration* const configuration;
  JobScheduler* const jobScheduler;
  MessageQueue* const messageQueue;
  PersistentStorage* const persistentStorage;

  SessionManagerState state;
  uint32_t numberOfSessions;
  void* currentJob;

  static bool dispatchAlert(SessionManager* const sessionManager);
  static bool dispatchStopSession(SessionManager* const sessionManager);
  
  void alert();
  void stopSession();

  void retrieveNumberOfSessionsFromPersistentStorage();
  void saveNumberOfSessionsToPersistentStorage();
  void increaseNumberOfSessions();

public:
  SessionManager(
    SessionManagerConfiguration* const configuration,
    JobScheduler* const jobScheduler,
    MessageQueue* const messageQueue,
    PersistentStorage* const persistentStorage
  );
  
  void Initialize();

  SessionManagerState State() const;
  uint32_t NumberOfSessions() const;

  void StartSession();
  void ForceStopSession();
  void ResetSessionCounter();
};

#endif