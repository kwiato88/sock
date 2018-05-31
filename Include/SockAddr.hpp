//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#pragma once

#ifdef _WIN32
#include <winsock2.h>
#endif
#include <string>

namespace sock
{

class Addr
{
public:
	Addr(const std::string& p_host, const std::string& p_port);
	~Addr();
	const addrinfo* operator->() const;
	operator const addrinfo& () const;
private:
	struct addrinfo *addr;
};

}
