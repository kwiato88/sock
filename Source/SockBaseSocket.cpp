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
#include <unistd.h>
#endif

#include "SockBaseSocket.hpp"
#include "SockSocketError.hpp"

namespace sock
{

BaseSocket::BaseSocket()
    : m_socket(INVALID_SOCKET)
{
    m_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == INVALID_SOCKET)
        throw LastError("Create socket failed");
}

BaseSocket::BaseSocket(SOCKET p_socketFd)
    : m_socket(p_socketFd)
{
}

BaseSocket::~BaseSocket()
{
    if(m_socket != INVALID_SOCKET)
    {
        try
        {
            close();
        } catch(const Error&)
        {
        }
    }
}

void BaseSocket::closeConnection()
{
    if(::shutdown(m_socket, SD_BOTH) != 0)
    {
        close();
        throw LastError("Shutdown socket failed");
    }
}

void BaseSocket::close()
{
    if(::closesocket(m_socket) !=0)
        throw LastError("Close socket failed");
    m_socket = INVALID_SOCKET;
}

} /* namespace winSock */

#ifndef _WIN32
int closesocket(sock::SOCKET p_socket)
{
    return ::close(p_socket);
}
#endif
