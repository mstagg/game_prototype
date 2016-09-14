#ifndef BROKER_H
#define BROKER_H

#include <map>
#include <string>

#include "Subscription.h"

class Broker
{
public:
	void addSubscription(std::string);
	void addMessage(std::string, Message*);
	bool hasMessage(std::string);
	Message* getMessage(std::string);
private:
	std::map<std::string, Subscription*> subscriptions;	// Hashmap to map strings to messsage subscriptions
};

#endif