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

    /**
     * @throw LastError
     */
    void closeConnection();

protected:
    BaseSocket();
    BaseSocket(SocketFd p_socket);
	BaseSocket(const BaseSocket&) = delete;
	BaseSocket& operator=(const BaseSocket&) = delete;
    void close();

private:
	int closeNative(SocketFd p_socket);
	int shutdownNative(SocketFd p_socket);
	SocketFd createNativeSocket();
	bool isInvalid(SocketFd p_socket);

protected:
	SocketFd m_socket;
};

}
