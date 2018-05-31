//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include "SockSocketError.hpp"
#include <iostream>
#include <errno.h>

namespace sock
{

SocketError::SocketError(std::string p_errorMsg) throw()
    : std::runtime_error(p_errorMsg)
{
}

#ifndef _WIN32
int WSAGetLastError()
{
    return errno;
}
#endif

} /* namespace winSock */
