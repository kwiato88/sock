//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "SockListeningSocket.hpp"
#include "SockSocketUtils.hpp"
#include "SockClientSocket.hpp"

using namespace std;

void SerwerSockMain()
{
    static const string host = "127.0.0.1";
    static const string port = "1234";
    sock::Data sendBuff;
    sock::Data recvBuff;
    boost::shared_ptr<sock::ListeningSocket> listener(new sock::ListeningSocket());

    listener->bind(host, port);
    listener->listen();
    boost::shared_ptr<sock::ClientSocket> client = listener->accept();

    recvBuff = client->receive();
    cout << "received first msg:" << recvBuff << endl;
    sendBuff = recvBuff;
    sendBuff += " OK";
    cout << "send response: " << sendBuff << endl;
    client->send(sendBuff);

    recvBuff = client->receive();
    cout << "received second msg:" << recvBuff << endl;
    sendBuff = recvBuff;
    sendBuff += " OK";
    cout << "send response: " << sendBuff << endl;
    client->send(sendBuff);

    client->closeConnection();
}

int main()
{
    sock::init();
    SerwerSockMain();
    sock::cleanup();

    return 0;
}
