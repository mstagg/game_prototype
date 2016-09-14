#include "Subscription.h"

void Subscription::enqueue(Message* m)
{
	this->messageQueue.push(m);
}

bool Subscription::hasMessage()
{
	return this->messageQueue.size() > 0;
}

Message* Subscription::dequeue()
{
	Message* m = this->messageQueue.front();
	this->messageQueue.pop();
	return m;
}