#include "Broker.h"

//TODO: SAFE DESTRUCTORS
//TODO: This class needs a way to keep track of added subscriptions

void Broker::addSubscription(std::string subscriptionName)
{
	this->subscriptions[subscriptionName] = new Subscription;
}

void Broker::addMessage(std::string subscriptionName, Message* message)
{
	this->subscriptions[subscriptionName]->enqueue(message);
}

bool Broker::hasMessage(std::string subscriptionName)
{
	return this->subscriptions[subscriptionName]->hasMessage();
}

Message* Broker::getMessage(std::string subscriptionName)
{
	Message* msg;
	if(this->hasMessage(subscriptionName))
	{
		msg = this->subscriptions[subscriptionName]->dequeue();
	}
	else
	{
		msg = new Message("empty");
	}

	return msg;
}