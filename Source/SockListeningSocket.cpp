//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <cstring>
#include "SockNative.hpp"
#include "SockListeningSocket.hpp"
#include "SockSocketError.hpp"
#include "SockClientSocket.hpp"
#include "SockAddr.hpp"

namespace sock
{

void ListeningSocket::bind(const std::string& p_host, const std::string& p_port)
{
	try
	{
		Addr server(p_host, p_port);
		if (::bind(m_socket, server->ai_addr, (int)server->ai_addrlen) != 0)
		{
			safeClose();
			throw LastError("Bind socket to " + p_host + "," + p_port + " failed");
		}
	}
	catch (ResolveAddressError&)
	{
		safeClose();
		throw;
	}
}

void ListeningSocket::listen(const int p_listeningQueueLength)
{
    if (::listen(m_socket, p_listeningQueueLength) != 0)
    {
		safeClose();
        throw LastError("Listening on socket failed");
    }
}

std::unique_ptr<ClientSocket> ListeningSocket::accept()
{
    SocketFd client(::accept(m_socket, NULL, NULL));
    if(isInvalid(client))
    {
        throw LastError("Accept client socket failed");
    }
	return std::make_unique<ClientSocket>(SocketFd(client));
}

} 
