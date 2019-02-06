#pragma once
#pragma once

#include <string>


class Message
{
public:
	Message();
	Message(short type);
	~Message();

	std::string get_msg();
	void add_content(const std::string key, const std::string value);


private:

	unsigned int msg_len;        //4 字节小端整数，表示整条消息（包括自身）长度（字节数）。消息长度出现两遍，二者相同
	unsigned int msg_len_h;

	unsigned short msg_type = 689;

	char secret = 0;
	char reserve = 0;

	//报文结尾必须为'\0'
	std::string content;     

};
