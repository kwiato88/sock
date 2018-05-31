//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE */
#ifdef _WIN32
#include <winsock2.h>
#endif

#include "SockSocketError.hpp"
#include "SockSocketUtils.hpp"

namespace sock
{

void init()
{
#ifdef _WIN32
    WSADATA wsaData;
    int errorCode = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(errorCode != 0)
        throw Error(std::string("WSAStartup failed with code") + std::to_string(errorCode));
#endif
}

void cleanup()
{
#ifdef _WIN32
    WSACleanup();
#endif
}

} //winSock
