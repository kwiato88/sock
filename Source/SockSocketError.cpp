//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include <errno.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif

#include "SockSocketError.hpp"

namespace sock
{

Error::Error(const std::string& p_errorMsg)
    : std::runtime_error(p_errorMsg)
{}

LastError::LastError(const std::string& p_errorMsg)
	: Error(p_errorMsg + ". Error code: " + std::to_string(errorCode()))
{}

int LastError::errorCode() const
{
#ifdef _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

ResolveAddressError::ResolveAddressError(const std::string& p_what, int p_errorCode)
	: Error(p_what + ". Error code: "
		+ std::to_string(p_errorCode) + ". Desc: " + ::gai_strerror(p_errorCode))
{}

}
