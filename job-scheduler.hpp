#ifndef JOB_SCHEDULER_HEADER
#define JOB_SCHEDULER_HEADER

#import "arduino-timer.h"

#ifndef MAXIMUM_NUMBER_OF_JOBS
#define MAXIMUM_NUMBER_OF_JOBS 16
#endif

class JobScheduler {
private:
  Timer<MAXIMUM_NUMBER_OF_JOBS, millis, void*> timer;

public:
  JobScheduler();

  typedef bool (*Handler)(void* opaque);

  void* ScheduleDelay(uint32_t const delay, Handler const handler, void* const argument);
  void* ScheduleRepeat(uint32_t const interval, Handler const handler, void* const argument);
  void CancelJob(void*& job);
  void Tick();
};

#endif