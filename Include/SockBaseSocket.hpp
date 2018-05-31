//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef BASESOCKET_HPP_
#define BASESOCKET_HPP_

#ifdef _WIN32
#include <winsock2.h>
#endif
#include <string>
#include <boost/noncopyable.hpp>

namespace sock
{

#ifndef _WIN32
#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1
#define IPPROTO_TCP    0
#define SD_BOTH         SHUT_RDWR
typedef int SOCKET;

int closesocket(SOCKET p_socket);
#endif

typedef std::string Data;

class BaseSocket : private boost::noncopyable
{
public:
    virtual ~BaseSocket();

    /**
     * @throw SocketError
     */
    void closeConnection();
protected:
    BaseSocket();
    BaseSocket(SOCKET p_socketFd);
protected:
    void close();
    SOCKET m_socket;
};

} /* namespace winSock */

#ifndef _WIN32
int closesocket(sock::SOCKET p_socket);
#endif

#endif /* BASESOCKET_HPP_ */
