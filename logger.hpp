#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#import "message-queue.hpp"

class Logger: public MessageQueueSubscriber {
public:
  Logger();

  void OnMessage(uint8_t const messageType, void* const payload) override;
};

#endif