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

	unsigned int msg_len;        //4 �ֽ�С����������ʾ������Ϣ�������������ȣ��ֽ���������Ϣ���ȳ������飬������ͬ
	unsigned int msg_len_h;

	unsigned short msg_type = 689;

	char secret = 0;
	char reserve = 0;

	//���Ľ�β����Ϊ'\0'
	std::string content;     

};
