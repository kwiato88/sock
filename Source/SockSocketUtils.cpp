//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE */
#ifdef _WIN32
#include <winsock2.h>
#include <sstream>
#include "SockSocketError.hpp"
#include "SockSocketUtils.hpp"
#endif
namespace sock
{

void init()
{
#ifdef _WIN32
    WSADATA wsaData;
    int errorCode = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(errorCode != 0)
    {
        std::ostringstream log;
        log << "ClientSocket::ClientSocket: WSAStartup failed with error: " << errorCode;
        throw SocketError(log.str());
    }
#endif
}

void cleanup()
{
#ifdef _WIN32
    WSACleanup();
#endif
}

} //winSock
