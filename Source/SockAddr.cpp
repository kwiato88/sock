//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include "SockNative.hpp"
#include "SockAddr.hpp"
#include "SockSocketError.hpp"

namespace sock
{

Addr::Addr(const std::string& p_host, const std::string& p_port)
	: addr(nullptr)
{
	struct addrinfo hint;
	::memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;

	int errorCode = ::getaddrinfo(p_host.c_str(), p_port.c_str(), &hint, &addr);
	if (errorCode != 0)
		throw ResolveAddressError(std::string("Failed to resolve address ") + p_host + "," + p_port, errorCode);
}

Addr::~Addr()
{
	if (addr != nullptr)
		::freeaddrinfo(addr);
}

const addrinfo* Addr::operator->() const
{
	return addr;
}

Addr::operator const addrinfo& () const
{
	return *addr;
}

}
