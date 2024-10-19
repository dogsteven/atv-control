#ifndef MESSAGE_QUEUE_HEADER
#define MESSAGE_QUEUE_HEADER

#import "push-only-array.hpp"

#ifndef MESSAGE_QUEUE_CAPACITY
#define MESSAGE_QUEUE_CAPACITY 16
#endif

class MessageQueueSubscriber {
public:
  virtual void OnMessage(uint8_t const messageType, void* const payload) = 0;
};

class MessageQueue {
private:
  PushOnlyArray<MESSAGE_QUEUE_CAPACITY, MessageQueueSubscriber*> subscribers;

public:
  MessageQueue();

  void AddSubscriber(MessageQueueSubscriber* const subscriber);
  void PublishMessage(uint8_t const messageType, void* const payload);
};

#endif