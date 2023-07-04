#include "Client.h"

Client::~Client()
{
	SDLNet_Quit();
}
//======================================================================
void Client::SendMessage(MainCharacter* mc)
{
	while (GetOnline())
	{
		//posx, posy
		sprintf_s(position, "%f %f \n", mc->GetPosition().x, mc->GetPosition().y);
		std::cout << "message sent from client" << std::endl;
		SDLNet_TCP_Send(GetClientSocket(), position, 1400);
	}
}
//======================================================================
void Client::ReceiveMessage()
{
	while (GetOnline())
	{
		int offset = 0;
		do {
			offset += SDLNet_TCP_Recv(GetServerSocket(), position + offset, 1400);
			if (offset <= 0)
				return;
		} while (position[strlen(position) - 1] != '\n');
		sscanf_s(position, "%f, %f \n", &(m_player.x), &(m_player.y));
		std::cout << position << std::endl;
		//std::cout << "message recieved from server" << std::endl;
		//close everything if there is no connection
		if (!GetClientSocket())
		{
			CloseAllSockets();
			std::cout << "You are disconected" << std::endl;
			SetOnline(false);
		}
	}
}
//======================================================================
void Client::MessageRecieverThread()
{
	//thread runs independently
	std::thread reciever(&Client::ReceiveMessage, this);
	reciever.detach();
}
/*void Client::MessageSenderThread(MainCharacter* mc)
{
	std::thread sender(&Client::SendMessage, mc, this);
	sender.detach();
}*/
float Client::GetPositionX()
{
	return m_player.x;
}
//======================================================================
float Client::GetPositionY()
{
	return m_player.y;
}
//======================================================================
