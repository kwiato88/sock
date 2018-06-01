//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include "SockConnection.hpp"
#include "SockSocketError.hpp"

namespace sock
{

Connection::Connection(const std::string& p_host, const std::string& p_port)
	: socket(std::make_unique<ClientSocket>()), isConnected(false)
{
	socket->connect(p_host, p_port);
	isConnected = true;
}

Connection::Connection(std::unique_ptr<ClientSocket> p_socket)
	: socket(std::move(p_socket))
{}

Connection::~Connection()
{
	try
	{
		if (isConnected)
			socket->closeConnection();
	}
	catch (Error&)
	{
	}
}

void Connection::send(const Data& p_data)
{
	socket->send(p_data);
}

Data Connection::receive()
{
	auto received = socket->receive();
	if (received.empty())
	{
		isConnected = false;
		throw Error("Receive failed. Connection clised by peer");
	}
	return received;
}

}
