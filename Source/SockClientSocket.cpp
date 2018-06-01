//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <cstring>
#include <memory>
#include "SockNative.hpp"
#include "SockClientSocket.hpp"
#include "SockAddr.hpp"
#include "SockSocketError.hpp"

#ifndef _WIN32
#define SOCKET_ERROR -1
#endif

namespace sock
{

ClientSocket::ClientSocket()
    : BaseSocket()
{}

ClientSocket::ClientSocket(SocketFd p_socketFd)
    : BaseSocket(p_socketFd)
{}

void ClientSocket::connect(const std::string& p_host, const std::string& p_port)
{
	try
	{
		Addr server(p_host, p_port);
		if (::connect(m_socket, server->ai_addr, (int)server->ai_addrlen) != 0)
		{
			safeClose();
			throw LastError("Connect socket to server " + p_host + "," + p_port + " failed");
		}
	}
	catch (ResolveAddressError&)
	{
		safeClose();
		throw;
	}
}

void ClientSocket::closeConnection()
{
	if (shutdownNative(m_socket) != 0)
	{
		safeClose();
		throw LastError("Shutdown socket failed");
	}
}

int ClientSocket::shutdownNative(SocketFd p_socket)
{
#ifndef _WIN32
#define SD_BOTH        SHUT_RDWR
#endif
	return ::shutdown(m_socket, SD_BOTH);
}

void ClientSocket::send(Data p_sendBuff)
{
    if(::send(m_socket, p_sendBuff.c_str(), p_sendBuff.length(), 0) == SOCKET_ERROR)
    {
		safeClose();
        throw LastError("Send data failed");
    }
}

Data ClientSocket::receive(unsigned int p_maxLength)
{
	std::shared_ptr<char> recvBuff(new char[p_maxLength], std::default_delete<char[]>());
    ::memset(recvBuff.get(),0, p_maxLength);

    int bytesReceived = ::recv(m_socket, recvBuff.get(), p_maxLength, 0);
    if(bytesReceived == SOCKET_ERROR)
    {
		safeClose();
        throw LastError("Receive data failed");
    }
    return bytesReceived == 0 ? Data() : Data(recvBuff.get(),recvBuff.get()+bytesReceived);
}

}
