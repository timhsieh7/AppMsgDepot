#include "stdafx.h"
#include "Message.h"
#include "MessageTypeDepot.h"
#include <utility>

/*
	MessageContainer:	Define the virtual function and message storage data struture to alter
						the message priority, order deliver
						

	EventHandler:		getMessage() will call the virtual getMessageEvent(const Message* msg).
						Application can dirive a class based on EventHandler, the override getMessageEvent(const Message* msg)
						will be called (callback) when a message has been arrived.
*/
MessageTypeDepot::MessageTypeDepot(MessageContainer* mc, EventHandler& e)
	:	_e(e)
{
	_msg_type_map = new std::map<std::string, MessageContainer*>();
	_msg_type_map->insert(std::pair<std::string, MessageContainer*>("red", mc));
	_msg_type_map->insert(std::pair<std::string, MessageContainer*>("yellow", mc));
	_msg_type_map->insert(std::pair<std::string, MessageContainer*>("blue", mc));
}


MessageTypeDepot::~MessageTypeDepot()
{ 
	delete _msg_type_map->find("red")->second;
	delete _msg_type_map;

}


void MessageTypeDepot::getMessageByType(std::string& msg_type) {

	const Message*	msgPtr;
	MessageContainer* messageContainer = _msg_type_map->find(msg_type)->second();
	if (nullptr != messageContainer) {
		msgPtr = messageContainer->getMessageRequest(msg_type);
		_e.getMessageEvent(msgPtr);
	}
	else {
		// errors, write to Logger "message_type is not valid." 
	}
}