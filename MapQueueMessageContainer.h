#ifndef MAPQUEUEMESSAGECONTAINER_H
#define	MAPQUEUEMESSAGECONTAINER_H

#include <map>
#include <queue>
#include <vector>
#include <mutex>
#include <algorithm>
#include "Message.h"
#include "MessageContainer.h"


class MapQueueMessageContainer :
	public MessageContainer
{
public:
	MapQueueMessageContainer();
	~MapQueueMessageContainer();

	const Message* getMessageRequest();

	void afterMessageDeliverd();
	void adjustMessageContainer();

	bool addMessage(const Message* msg, int priority);

private:
	std::vector<int>	_priority_vector;
	std::map<int, std::queue<const Message*>*> *_priority_map;
	std::mutex	_mtx_queue;
	std::mutex  _mtx_add_queue
	};

#endif	/* MAPQUEUEMESSAGECONTAINER_H */
