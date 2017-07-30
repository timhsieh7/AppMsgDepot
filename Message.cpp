#include "stdafx.h"
#include "Message.h"

Message::Message()
	:	_type(NULL),
		_priority(0),
		_data(nullptr)
{
}


Message::Message(std::string type, int priority, int sz, char* msg)
	:	_type(type),
		_priority(priority),
	    _data(new char[sz + 1])
{
	memcpy(_data, msg, sz);

}



Message::Message(char* rawMsgByte, int sz)
	: _type(NULL),
	_priority(0),
	_data(nullptr)
{
	_type;		//=	bytes off set from head, shifting bytes by endianness (big-endian / little-endian ), map valune to string
	_priority;  //= bytes off set from head, shifting bytes by endianness (big-endian / little-endian )
	_data;		// memccpy( _data, rawMsgByte + offset, sz - header_size);
}



Message::~Message()
{
	delete _data;
}
