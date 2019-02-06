#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include "Message.h"
#include "Util.h"
#pragma comment(lib, "ws2_32.lib")
//1870001
const std::string ROOM_ID = "1870001";
const std::string GROUP_ID = "-9999";

enum MSG_TYPE
{
	BARRAGE_MSG = 0,
	LOGINRES_MSG,
	OTHER_MSG
};

class Client
{
public:
	
	static Client* creatClient();  //����ģʽ��ȡ����

	void send_login_msg();      

	void send_group_msg();   

	void send_keep_live_msg(int time);     //����������

	void recv_msg();

	int get_msg_type(std::string str);
	
	void print(std::string);   //��ʽ�����



private:	
	static Client *client;

	Client();
	~Client();
	
	void Init();
	int socket_fd;

	
	const std::string host_name = "openbarrage.douyutv.com";
	const unsigned int port = 8601;

};

