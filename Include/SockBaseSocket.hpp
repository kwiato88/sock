//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#pragma once

#ifdef _WIN32
#include <winsock2.h>
#endif
#include <string>
#include <boost/serialization/strong_typedef.hpp>

namespace sock
{

#ifndef _WIN32
typedef int SOCKET;
#endif

typedef std::string Data;
BOOST_STRONG_TYPEDEF(SOCKET, SocketFd);

class BaseSocket
{
public:
    virtual ~BaseSocket();

protected:
    BaseSocket();
    BaseSocket(SocketFd p_socket);
	BaseSocket(const BaseSocket&) = delete;
	BaseSocket& operator=(const BaseSocket&) = delete;
    void close();
	void safeClose();
	bool isInvalid(SocketFd p_socket);

private:
	int closeNative(SocketFd p_socket);
	SocketFd createNativeSocket();

protected:
	SocketFd m_socket;
};

}
