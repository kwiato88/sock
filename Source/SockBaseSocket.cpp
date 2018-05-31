//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include "SockNative.hpp"
#include "SockBaseSocket.hpp"
#include "SockSocketError.hpp"

#ifndef _WIN32
#define INVALID_SOCKET -1
#endif

namespace sock
{

BaseSocket::BaseSocket()
    : m_socket(INVALID_SOCKET)
{
    m_socket = createNativeSocket();
    if(isInvalid(m_socket))
        throw LastError("Create socket failed");
}

BaseSocket::BaseSocket(SocketFd p_socket)
    : m_socket(p_socket)
{}

BaseSocket::~BaseSocket()
{
    if(!isInvalid(m_socket))
		safeClose();
}

void BaseSocket::closeConnection()
{
    if(shutdownNative(m_socket) != 0)
    {
		safeClose();
        throw LastError("Shutdown socket failed");
    }
}

void BaseSocket::close()
{
	bool errorOccured = closeNative(m_socket) != 0;
	m_socket = INVALID_SOCKET;
	if (errorOccured)
		throw LastError("Close socket failed");
}

void BaseSocket::safeClose()
{
	closeNative(m_socket);
	m_socket = INVALID_SOCKET;
}

bool BaseSocket::isInvalid(SocketFd p_socket)
{
	return p_socket == INVALID_SOCKET;
}

int BaseSocket::closeNative(SocketFd p_socket)
{
#ifdef _WIN32
	return ::closesocket(p_socket);
#else
	return ::close(p_socket);
#endif
}

int BaseSocket::shutdownNative(SocketFd p_socket)
{
#ifndef _WIN32
#define SD_BOTH        SHUT_RDWR
#endif
	return ::shutdown(m_socket, SD_BOTH);
}

SocketFd BaseSocket::createNativeSocket()
{
#ifndef _WIN32
#define IPPROTO_TCP    0
#endif
	return SocketFd(::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
}

}
