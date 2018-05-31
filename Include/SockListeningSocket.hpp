//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#pragma once

#include <string>
#include <memory>
#include "SockBaseSocket.hpp"

namespace sock
{

class ClientSocket;

class ListeningSocket: public BaseSocket
{
public:

    /**
     * @throw ResolveAddressError, LastError
     */
    void bind(const std::string& p_host, const std::string& p_port);

    /**
     * @throw LastError
     */
    void listen(const int p_listeningQueueLength = DEFAULT_LISTEN_QUEUE_LENGTH);

    /**
     * @throw LastError
     */
    std::unique_ptr<ClientSocket> accept();

    static const int DEFAULT_LISTEN_QUEUE_LENGTH = 10;
};

}
