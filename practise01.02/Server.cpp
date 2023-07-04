#include "Server.h"

Server::~Server()
{
	SDLNet_Quit();
}
//======================================================================
bool Server::Listen()
{
	if (!GetServerSocket())
	{
		std::cout << "server socket closed for clients" << std::endl;
	}
	else
	{
		std::cout << "server socket open for clients" << std::endl;
	}

	while (!GetClientSocket())
	{
		SetClientSocket(SDLNet_TCP_Accept(GetServerSocket()));
		std::cout << ".";
		SDL_Delay(500u);
	}
	SetOnline(true);
	return true;
}
//======================================================================
void Server::SendMessage(MainCharacter* mc)
{
	while (GetOnline())
	{
		//posx, posy
		sprintf_s(position,"%f %f \n" , mc->GetPosition().x, mc->GetPosition().y);
		std::cout << position << std::endl;
		//std::cout << "message sent from server" << std::endl;
		SDLNet_TCP_Send(GetClientSocket(), position, 1400);
	}
	
}
//======================================================================
void Server::ReceiveMessage()
{
	while (GetOnline())
	{
		int offset = 0;
		do {
			offset += SDLNet_TCP_Recv(GetServerSocket(), position + offset, 1400);
			if (offset <= 0)
				return;
		} while (position[strlen(position) - 1] != '\n');
		sscanf_s(position, "%f, %f \n",&(m_player.x), &(m_player.y));
		std::cout << "message recieved from client" << std::endl;
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
void Server::MessageRecieverThread()
{
	std::thread reciever(&Server::ReceiveMessage, this);
	reciever.detach();
}
/*void Server::MessageSenderThread(MainCharacter* mc)
{
	std::thread sender(&Server::SendMessage,&mc);
	sender.detach();
}*/
float Server::GetPositionX()
{
	return m_player.x;
}
//======================================================================
float Server::GetPositionY()
{
	return m_player.y;
}
//======================================================================

