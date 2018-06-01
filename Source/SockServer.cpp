//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include "SockServer.hpp"

namespace sock
{

Server::Server(const std::string& p_host, const std::string& p_port)
{
	socket.bind(p_host, p_port);
	socket.listen();
}

std::unique_ptr<Connection> Server::accept()
{
	return std::make_unique<Connection>(socket.accept());
}

}
