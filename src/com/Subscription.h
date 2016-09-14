#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <map>
#include <string>
#include <queue>

#include "Message.h"

class Subscription
{
public:
	void enqueue(Message*);
	bool hasMessage();
	Message* dequeue();
private:
	std::queue<Message*> messageQueue;	// Hashmap to map strings to messsage subscriptions
};

#endif