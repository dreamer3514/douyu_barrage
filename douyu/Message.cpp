#include "Message.h"
#include <string>
#include <iostream>



Message::Message()
{
	
}
Message::Message(short type) :msg_type(type)
{
}
Message::~Message()
{
}

void Message::add_content(std::string key, std::string value)
{
	std::string::iterator ite_k = key.begin();
	std::string::iterator ite_v = value.begin();
	
	while (ite_k != key.end())
	{
		if (*ite_k == '/')
		{
			content.append("@S", 2);
		}
		else if (*ite_k == '@')
		{
			content.append("@A", 2);
		}
		else
		{
			content += *ite_k;
		}

		ite_k++;
	}

	content.append("@=", 2);

	while (ite_v != value.end())
	{
		if (*ite_v == '/')
		{
			content.append("@S", 2);
		}
		else if (*ite_v == '@')
		{
			content.append("@A", 2);
		}
		else
		{
			content += *ite_v;
		}

		ite_v++;
	}
	content.append("/", 1);
}

std::string Message::get_msg()
{
	std::string msg;
	content += '\0';
	msg_len = content.length()+8;
	msg_len_h = msg_len;
	msg.append((const char*)&msg_len,sizeof(msg_len));
	msg.append((const char*)&msg_len_h, sizeof(msg_len_h));
	msg.append((const char*)&msg_type, sizeof(msg_type));
	msg.append((const char*)&secret, sizeof(secret));
	msg.append((const char*)&reserve, sizeof(reserve));

	msg.append(content.c_str(),content.length());
	
	return msg;

}