#include "TCPSocket.h"

bool TCPSocket::Initialise(const char* address)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	if (SDLNet_Init() == 1)
	{
		std::cout << "SDL net could not initialise" << std::endl;
		return 1;
	}

	if (SDLNet_ResolveHost(&m_IP, address, PORT) == -1)
	{
		std::cout << "could not establish connection" << std::endl;
		return 1;
	}
	std::cout << "SDL net is initialized" << std::endl;
	return true;
}
//======================================================================
bool TCPSocket::OpenServerSocket()
{
	m_serverSocket = SDLNet_TCP_Open(&m_IP);

	if (!m_serverSocket)
	{
		std::cout << "error: server socket is not created" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "server socket is open" << std::endl;
		SetOnline(true);
		return 0;
	}
	return 0;
}
//======================================================================
bool TCPSocket::OpenClientSocket()
{
	m_clientSocket = SDLNet_TCP_Open(&m_IP);

	if (!m_clientSocket)
	{
		std::cout << "error: client socket not built" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "client socket open, waiting for client" << std::endl;
		SetOnline(true);
		return 0;
	}
	return 0;
}
//======================================================================
void TCPSocket::CloseAllSockets()
{
	SDLNet_TCP_Close(m_serverSocket);
	SDLNet_TCP_Close(m_clientSocket);
}
//======================================================================
void TCPSocket::ShutDown()
{
	SDLNet_Quit();
}
//======================================================================
void TCPSocket::SetIPAddress(IPaddress ip)
{
	m_IP = ip;
}
IPaddress TCPSocket::GetIPAddress()
{
	return m_IP;
}
//======================================================================
void TCPSocket::SetServerSocket(TCPsocket openSocket)
{
	m_serverSocket = openSocket;
}
TCPsocket TCPSocket::GetServerSocket()
{
	return m_serverSocket;
}
//======================================================================
void TCPSocket::SetClientSocket(TCPsocket openSocket)
{
	m_clientSocket = openSocket;
}
TCPsocket TCPSocket::GetClientSocket()
{
	return m_clientSocket;
}
//======================================================================
void TCPSocket::SetOnline(bool online)
{
	m_online = online;
}
bool TCPSocket::GetOnline()
{
	return m_online;
}
