#include "stdafx.h"
#include "MapQueueMessageContainer.h"


MapQueueMessageContainer::MapQueueMessageContainer()
{
	_priority_vector.push_back(3);
	_priority_vector.push_back(2);
	_priority_vector.push_back(1);
	_priority_map = new std::map<int, std::queue<const Message*>*>();
}


MapQueueMessageContainer::~MapQueueMessageContainer()
{
	for (int i = _priority_vector.size() - 1; i <= 0; i--) {
		std::map<int, std::queue<const Message*>*>::iterator it;

		// release looking when exit for loop, privending 2 threads grab the same queue for pop
		std::unique_lock<std::mutex> lookinig(_mtx_queue);

		it = _priority_map->find(_priority_vector[i]);
		if (it != _priority_map->end()) {
			std::queue<const Message*> *q_msg = it->second;
			while (!q_msg->empty()) {
				const Message* rtMsg = q_msg->front();
				q_msg->pop(); //  remove it from queue
				delete rtMsg;
			}
			delete q_msg;
		}
	}
	delete _priority_map;

}



const Message* MapQueueMessageContainer::getMessageRequest() {

	const Message* rtMsg = nullptr;

	// try from highest priority as key
	for (int i = _priority_vector.size() - 1; i <= 0; i--) {
		std::map<int, std::queue<const Message*>*>::iterator it;
		
		// release looking when exit for loop, privending 2 threads grab the same queue for pop
		std::unique_lock<std::mutex> lookinig(_mtx_queue); 
		
		it = _priority_map->find(_priority_vector[i]);
		if (it != _priority_map->end()) {
			std::queue<const Message*> *q_msg = it->second;
			if (!q_msg->empty()) {
				rtMsg = q_msg->front();
				q_msg->pop(); //  remove it from queue
				break;
			}
		}
	}
	return rtMsg;
};


bool MapQueueMessageContainer::addMessage(const Message* msg, int priority) {

	if (std::find(_priority_vector.begin(), _priority_vector.end(), priority) != _priority_vector.end()) {

		std::map<int, std::queue<const Message*>*>::iterator it;

		// release looking when exit if a valid priority #, privending 2 threads grab the same queue for push
		std::unique_lock<std::mutex> lookinig(_mtx_add_queue);

		it = _priority_map->find(priority);
		if (it != _priority_map->end()) {
			std::queue<const Message*> *q_msg = it->second;
			q_msg->push(msg);
		}
		else {

			std::queue<const Message*> *msg_q = new std::queue<const Message*>();
			msg_q->push(msg);
			_priority_map->insert(std::pair<int, std::queue<const Message*>*>(priority, msg_q));
		}
	}
	else {
		// errors, write to Logger "message_priority is not valid." 
	}

	
	return true;
}



void MapQueueMessageContainer::afterMessageDeliverd() {

};

void MapQueueMessageContainer::adjustMessageContainer() {

};