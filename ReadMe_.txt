The Application of client API is in
MessageTypeDepot.cpp

We use 
std::map<std::string, MessageContainer*> 
a message type as key, the map vaule, MessageContainer class, to deliver messaage

Application can derive a class, in our case, it is  
class MapQueueMessageContainer : public MessageContainer
define 
    virtual const Message* getMessageRequest(std::string msgType) {};
	virtual void afterMessageDeliverd() {};
	virtual void adjustMessageContainer() {};

to alter the message priority and order.

in MapQueueMessageContainer 
we use queue for FIFO and queue pop remove the message from storage.
Each priority has it own queue.  This arrangement fave permanence of get Message

EventHandler is final message deliver callback.
Application could do what they like in their derived 
virtual void getMessageEvent(const Message* msg) {};
for example, push into a concurrent queue and let another thread de-queue for asynchronized
message process.
 