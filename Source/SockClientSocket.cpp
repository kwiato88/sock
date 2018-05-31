//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifdef _WIN32
#include <ws2tcpip.h>
#include <windows.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#endif
#include <iostream>
#include <sstream>
#include <cstring>
#include <memory>
#include "SockClientSocket.hpp"
#include "SockSocketError.hpp"

namespace sock
{

ClientSocket::ClientSocket()
    : BaseSocket()
{
}

ClientSocket::ClientSocket(SOCKET p_socketFd)
    : BaseSocket(p_socketFd)
{
}

void ClientSocket::connect(std::string p_host, std::string p_port)
{
    struct addrinfo *serwerAddr = NULL, hint;
    ::memset( &hint, 0,  sizeof(hint) );
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    int errorCode = ::getaddrinfo(p_host.c_str(), p_port.c_str(), &hint, &serwerAddr);
    if (errorCode != 0)
    {
        std::ostringstream log;
        log << "ClientSocket::connect: getaddrinfo failed with error: " << errorCode << " - " << ::gai_strerror(errorCode);
        close();
        throw SocketError(log.str());
    }

    if(::connect( m_socket, serwerAddr->ai_addr, (int)serwerAddr->ai_addrlen) !=0)
    {
        close();
    }
    ::freeaddrinfo(serwerAddr);
    if (m_socket == INVALID_SOCKET)
    {
        std::ostringstream log;
        log << "ClientSocket::connect: connect failed with error: " << WSAGetLastError();
        throw SocketError(log.str());
    }
}

void ClientSocket::send(Data p_sendBuff)
{
    if(::send(m_socket, p_sendBuff.c_str(), p_sendBuff.length(), 0) == SOCKET_ERROR)
    {
        std::ostringstream log;
        log << "ClientSocket::send: send failed with error: " << WSAGetLastError();
        close();
        throw SocketError(log.str());
    }
}

Data ClientSocket::receive(unsigned int p_maxLength)
{
	std::shared_ptr<char> recvBuff(new char[p_maxLength], std::default_delete<char[]>());
    ::memset(recvBuff.get(),0,100);

    int bytesReceived = ::recv(m_socket, recvBuff.get(), p_maxLength, 0);
    if(bytesReceived < 0)
    {
        std::ostringstream log;
        log << "ClientSocket::receive: recv failed with error: " << WSAGetLastError();
        close();
        throw SocketError(log.str());;
    }
    return bytesReceived == 0 ? Data() : Data(recvBuff.get(),recvBuff.get()+bytesReceived);
}

} /* namespace winSock */
