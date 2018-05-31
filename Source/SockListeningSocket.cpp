//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <cstring>
#include "SockNative.hpp"
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
        close();
		throw ResolveAddressError(std::string("Bind socket: failed to resolve address ") + p_host + "," + p_port, errorCode);
    }

    if(::bind(m_socket, serwerAddr->ai_addr, (int)serwerAddr->ai_addrlen) != 0)
    {
        close();
    }
    ::freeaddrinfo(serwerAddr);
    if (m_socket == INVALID_SOCKET)
        throw LastError("Bind socket to " + p_host + "," + p_port + " failed");
}

void ListeningSocket::listen(const int p_listeningQueueLength)
{
    if (::listen(m_socket, p_listeningQueueLength) != 0)
    {
        close();
        throw LastError("Listening on socket failed");
    }
}

boost::shared_ptr<ClientSocket> ListeningSocket::accept()
{
    SOCKET clientFd = ::accept(m_socket, NULL, NULL);
    if(clientFd == INVALID_SOCKET)
    {
        close();
        throw LastError("Accept client socket failed");
    }
    boost::shared_ptr<ClientSocket> client(new ClientSocket(SocketFd(clientFd)));
    return client;
}

} 
