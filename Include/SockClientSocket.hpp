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
     * @throw SocketError
     */
    ClientSocket();
    ClientSocket(SocketFd p_socketFd);

    /**
     * @throw SocketError
     */
    void connect(std::string p_host, std::string p_port);

    /**
     * @throw SocketError
     */
    void send(Data p_sendBuff);

    /**
     * @throw SocketError
     */
    Data receive(unsigned int p_maxLength = DEFAULT_MAX_DATA_LENGTH);

    static const unsigned int DEFAULT_MAX_DATA_LENGTH = 512;
};

}
