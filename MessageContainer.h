#ifndef MESSAGECONTAINER_H
#define	MESSAGECONTAINER_H


#include <string>
#include "Message.h"


class MessageContainer
{
public:
	MessageContainer();
	~MessageContainer();    // base class destructor should be pure virtual 

	virtual const Message* getMessageRequest(std::string msgType) {};
	virtual void afterMessageDeliverd() {};
	virtual void adjustMessageContainer() {};

};


#endif	/* MESSAGECONTAINER_H */