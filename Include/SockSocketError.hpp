//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef SOCKETERROR_HPP_
#define SOCKETERROR_HPP_

#include <stdexcept>
#include <string>

namespace sock
{

struct SocketError: public std::runtime_error
{
    SocketError(std::string p_errorMsg);
};

#ifndef _WIN32
int WSAGetLastError();
#endif

} /* namespace winSock */
#endif /* SOCKETERROR_HPP_ */
