//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#ifndef LISTENINGSOCKET_HPP_
#define LISTENINGSOCKET_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include "SockBaseSocket.hpp"

namespace sock
{

class ClientSocket;

class ListeningSocket: public BaseSocket
{
public:

    /**
     * @throw SocketError
     */
    void bind(std::string p_host, std::string p_port);

    /**
     * @throw SocketError
     */
    void listen(const int p_listeningQueueLength = DEFAULT_LISTEN_QUEUE_LENGTH);

    /**
     * @throw SocketError
     */
    boost::shared_ptr<ClientSocket> accept();

    static const int DEFAULT_LISTEN_QUEUE_LENGTH = 10;
};

} /* namespace winSock */

#endif /* LISTENINGSOCKET_HPP_ */
