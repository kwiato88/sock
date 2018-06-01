//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#pragma once

#include <string>
#include <memory>
#include "SockListeningSocket.hpp"
#include "SockConnection.hpp"

namespace sock
{

class Server
{
public:
	/**
	* throws Error
	*/
	Server(const std::string& p_host, const std::string& p_port);
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;

	/**
	* throws Error
	*/
	std::unique_ptr<Connection> accept();

private:
	ListeningSocket socket;
};

}
