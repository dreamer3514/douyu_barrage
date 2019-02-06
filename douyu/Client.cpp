#include "Client.h"

static Client *client = nullptr;
Client::Client()
{
	Init();
}

Client::~Client()
{
}
Client* Client::client = new Client();
Client* Client::creatClient()
{
	return client;
}

int Client::get_msg_type(std::string str)
{
	std::string type = Util::getValue(str, "type");
	
	
	if(type.compare("chatmsg")==0)
	{
		//std::cout<<"弹幕"<<std::endl;
		return BARRAGE_MSG;
	}
	else if(type.compare("loginres") == 0)
	{
		//std::cout << "登录回复" << std::endl;
		return LOGINRES_MSG;
	}
	else
	{
		//std::cout << "其他类型" << std::endl;
		return OTHER_MSG;
	}
}
void Client::Init()
{
	unsigned long lgIP = inet_addr(host_name.data());
	if (lgIP != INADDR_NONE)
	{
		WSACleanup();
		return ;
	}
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1, 1), &wsaData);

	hostent *host;
	host = gethostbyname(host_name.c_str());
	if (host == nullptr)
	{
		std::cout << "域名错误" << std::endl;
		return ;
	}

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		std::cout << "socket建立错误" << std::endl;
		return ;

	}

	sockaddr_in  addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr = *((in_addr*)host->h_addr);

	int con_ret = connect(socket_fd, (sockaddr*)&addr, sizeof(addr));
	if (con_ret == -1)
	{
		std::cout << "连接失败" << std::endl;
		return ;
	}
	std::cout << "连接成功" << std::endl; 
}

void Client::send_login_msg()
{
	//构造消息
	Message msg;
	msg.add_content("type", "loginreq");
	msg.add_content("roomid", ROOM_ID);
	//发送
	std::string _msg = msg.get_msg();
	int ret = send(socket_fd, _msg.data(), _msg.length(), 0);
	if (ret == -1)
	{
		std::cout << "发送登录信息失败" << std::endl;
	}
	std::cout<<"发送登录信息"<<std::endl;
}
void Client::send_group_msg()
{
	Message msg;
	msg.add_content("type", "joingroup");
	msg.add_content("rid", ROOM_ID);
	msg.add_content("gid", GROUP_ID);
	std::string _msg = msg.get_msg();
	int ret = send(socket_fd, _msg.data(), _msg.length(), 0);
	if (ret == -1)
	{
		std::cout << "发送入组信息失败" << std::endl;
	}
	std::cout << "发送入组信息" << std::endl;
}

void Client::recv_msg()
{
	std::cout << "接收消息" << std::endl;
	while (true)
	{
		//std::cout << "接收消息循环" << std::endl;
		char len_buf[4];
		int ret = recv(socket_fd, len_buf, 4, 0);
		if (ret == -1)
		{
			std::cout << "接收消息失败" << std::endl;
			continue;
		}
		unsigned int len = (len_buf[3] & 0xffffffff) << 24 |       //将4个字节的char转换为1个整数
			(len_buf[2] & 0x00ffffff) << 16 |
			(len_buf[1] & 0x0000ffff) << 8 |
			len_buf[0] & 0x000000ff;
		if (len < 8 || len > 3000)
		{
			continue;
		}
		//std::cout << "接收消息长度：" << len <<std::endl;
		char buf[4096];
		ret = recv(socket_fd, buf, len, 0);
		if (ret == -1)
		{
			std::cout << "接收消息失败" << std::endl;
		}
		std::string _msg(buf, ret);

		std::string msg(_msg.c_str() + 8, _msg.length()-8);
		
		//解码 格式处理 
		int type = get_msg_type(msg);
		
		switch (type)
		{
		case 0:
			print(msg);
			//std::cout << msg << std::endl;
			break;
		case 1:
			std::cout << "登录成功" << std::endl;
			break;
		default:
			break;
		}

		//std::cout << msg << std::endl;
	}
}

void Client::send_keep_live_msg(int time)
{
	Message msg;

	std::string _time = std::to_string(time);

	msg.add_content("type", "keeplive");
	msg.add_content("tick", _time);

	std::string _msg = msg.get_msg();
	int ret = send(socket_fd, _msg.data(), _msg.length(), 0);
	if (ret == -1)
	{
		std::cout << "发送心跳信息失败" << std::endl;
	}
	//std::cout << "发送心跳信息" << std::endl;
}

void Client::print(std::string msg)
{
	//std::cout << "解析" << std::endl;
	std::string name = Util::decode(Util::getValue(msg, "nn"));
	std::string barrage = Util::decode(Util::getValue(msg, "txt"));
	std::cout << name << " : " << barrage << std::endl;
}