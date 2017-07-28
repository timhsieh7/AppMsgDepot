#pragma once

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

#include "Message.h"
class EventHandler
{
public:
	EventHandler() {
	};

	~EventHandler();    
	
	virtual void getMessageEvent(const Message* msg) {};
	
};

#endif	/* EVENTHANDLER_H */