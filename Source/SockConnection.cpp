//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include "SockConnection.hpp"

namespace sock
{

Connection::Connection(const std::string& p_host, const std::string& p_port)
	: socket()
{
	socket.connect(p_host, p_port);
}

Connection::~Connection()
{
	socket.closeConnection();
}

void Connection::send(const Data& p_data)
{
	socket.send(p_data);
}

Data Connection::receive()
{
	return socket.receive();
}

}
