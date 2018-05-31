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
#include <sstream>
#include <cstring>
#include "SockListeningSocket.hpp"
#include "SockSocketError.hpp"
#include "SockClientSocket.hpp"

namespace sock
{

void ListeningSocket::bind(std::string p_host, std::string p_port)
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

    if(::bind(m_socket, serwerAddr->ai_addr, (int)serwerAddr->ai_addrlen) != 0)
    {
        close();
    }
    ::freeaddrinfo(serwerAddr);
    if (m_socket == INVALID_SOCKET)
    {
        std::ostringstream log;
        log << "ListeningSocket::bind: bind failed with error: " << WSAGetLastError();
        throw SocketError(log.str());
    }

}

void ListeningSocket::listen(const int p_listeningQueueLength)
{
    if (::listen(m_socket, p_listeningQueueLength) != 0)
    {
        std::ostringstream log;
        log << "ListeningSocket::listen: listen failed with error: " << WSAGetLastError();
        close();
        throw SocketError(log.str());
    }
}

boost::shared_ptr<ClientSocket> ListeningSocket::accept()
{
    SOCKET clientFd = ::accept(m_socket, NULL, NULL);
    if(clientFd == INVALID_SOCKET)
    {
        std::ostringstream log;
        log << "ListeningSocket::accept: accept failed with error: " << WSAGetLastError();
        close();
        throw SocketError(log.str());
    }
    boost::shared_ptr<ClientSocket> client(new ClientSocket(clientFd));
    return client;
}

} /* namespace winSock */
