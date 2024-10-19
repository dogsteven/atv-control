#import "message-queue.hpp"

MessageQueue::MessageQueue() {}

void MessageQueue::AddSubscriber(MessageQueueSubscriber *const subscriber) {
  this->subscribers.Push(subscriber);
}

void MessageQueue::PublishMessage(const uint8_t messageType, void *const payload) {
  uint8_t const numberOfSubscribers = this->subscribers.Size();

  for (uint8_t i = 0; i < numberOfSubscribers; ++i) {
    this->subscribers.Read(i)->OnMessage(messageType, payload);
  }
}