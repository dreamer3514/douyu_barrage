#include "Client.h"

void keep_live(Client *client)
{
	while (true)
	{
		int time = GetTickCount();
		client->send_keep_live_msg(time);
		Sleep(45000);
	}
}
int main()
{
	Client *client = Client::creatClient();

	client->send_login_msg();
	client->send_group_msg();
	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)keep_live, client, 0, NULL);
	client->recv_msg();
}