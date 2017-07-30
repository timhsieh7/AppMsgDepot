#ifndef MESSAGETYPEDEDOT_H
#define	MESSAGETYPEDEDOT_H

#include <stdlib.h>
#include <map>
#include <string>

#include "MessageContainer.h"
#include "EventHandler.h"

/*
MessageContainer:	Define the virtual function and message storage data struture to alter
					the message priority, order deliver

	EventHandler :	getMessage() will call the virtual getMessageEvent(const Message* msg).
					Application can dirive a class based on EventHandler, the override getMessageEvent(const Message* msg)
					will be called(callback) when a message has been arrived.
*/
class MessageTypeDepot
{
public:
	MessageTypeDepot(MessageContainer* mc, EventHandler& e );
	~MessageTypeDepot();

	std::map<std::string, MessageContainer*> *_msg_type_map;

	void getMessageByType(std::string& msg_type);

private:
	EventHandler _e;
};

#endif	/* MESSAGETYPEDEDOT_H */



