#ifndef MESSAGE_H
#define	MESSAGE_H

#include <string>

class Message
{
public:
	Message();
	Message(std::string type, int priority, int sz, char* msg);
	Message(char* rawMsgByte, int sz);

	~Message();

	std::string		_type;
	int				_priority;
	char*			_data;
	
};

#endif	/* MESSAGE_H */

