//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <cstring>
#include <memory>
#include "SockNative.hpp"
#include "SockClientSocket.hpp"
#include "SockSocketError.hpp"

#ifndef _WIN32
#define SOCKET_ERROR -1
#endif

namespace sock
{

Addr::Addr(const std::string& p_host, const std::string& p_port)
	: addr(nullptr)
{
	struct addrinfo hint;
	::memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;

	int errorCode = ::getaddrinfo(p_host.c_str(), p_port.c_str(), &hint, &addr);
	if (errorCode != 0)
		throw ResolveAddressError(std::string("Failed to resolve address ") + p_host + "," + p_port, errorCode);
}

Addr::~Addr()
{
	if (addr != nullptr)
		::freeaddrinfo(addr);
}

const addrinfo* Addr::operator->() const
{
	return addr;
}

Addr::operator const addrinfo& () const
{
	return *addr;
}

ClientSocket::ClientSocket()
    : BaseSocket()
{
}

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
			close();
			throw LastError("Connect socket to server " + p_host + "," + p_port + " failed");
		}
	}
	catch (ResolveAddressError&)
	{
		close();
		throw;
	}
}

void ClientSocket::send(Data p_sendBuff)
{
    if(::send(m_socket, p_sendBuff.c_str(), p_sendBuff.length(), 0) == SOCKET_ERROR)
    {
        close();
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
        close();
        throw LastError("Receive data failed");
    }
    return bytesReceived == 0 ? Data() : Data(recvBuff.get(),recvBuff.get()+bytesReceived);
}

}
