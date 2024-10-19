#import "job-scheduler.hpp"

JobScheduler::JobScheduler() {}

void* JobScheduler::ScheduleDelay(const uint32_t delay, const Handler handler, void *const argument) {
  return this->timer.in(delay, handler, argument);
}

void* JobScheduler::ScheduleRepeat(const uint32_t interval, const Handler handler, void *const argument) {
  return this->timer.every(interval, handler, argument);
}

void JobScheduler::CancelJob(void*& job) {
  this->timer.cancel(job);
}

void JobScheduler::Tick() {
  this->timer.tick();
}