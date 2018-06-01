//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#pragma once

#include <string>
#include "SockBaseSocket.hpp"

namespace sock
{

class ClientSocket : public BaseSocket
{
public:

    /**
     * @throw LastError
     */
    ClientSocket();
    ClientSocket(SocketFd p_socketFd);

    /**
     * @throw ResolveAddressError, LastError
     */
    void connect(const std::string& p_host, const std::string& p_port);

	/**
	* @throw LastError
	*/
	void closeConnection();

    /**
     * @throw LastError
     */
    void send(Data p_sendBuff);

    /**
     * @throw LastError
     */
    Data receive(unsigned int p_maxLength = DEFAULT_MAX_DATA_LENGTH);

    static const unsigned int DEFAULT_MAX_DATA_LENGTH = 1024;

private:
	int shutdownNative(SocketFd p_socket);
};

}
