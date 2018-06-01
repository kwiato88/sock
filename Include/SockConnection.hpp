//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#pragma once

#include <string>
#include "SockClientSocket.hpp"

namespace sock
{

class Connection
{
public:
	Connection(const std::string& p_host, const std::string& p_port);
	~Connection();
	Connection(const Connection&) = delete;
	Connection& operator=(const Connection&) = delete;

	void send(const Data& p_data);
	Data receive();

private:
	ClientSocket socket;
};

}
