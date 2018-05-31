//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "SockClientSocket.hpp"
#include "SockSocketUtils.hpp"
#include "SockListeningSocket.hpp"

using namespace std;

void ClientSockMain()
{
    static const string host = "127.0.0.1";
    static const string port = "1234";
    sock::Data sendBuff;
    sock::Data recvBuff;
    boost::shared_ptr<sock::ClientSocket> client(new sock::ClientSocket());

    client->connect(host, port);

    sendBuff = "first msg";
    cout << "send first mesg: " << sendBuff << endl;
    client->send(sendBuff);
    recvBuff = client->receive();
    if(recvBuff.empty())
    {
        cout << "connection closed" << endl;
        return;
    }
    cout << "received first msg: " << recvBuff << endl;


    sendBuff = "secnd msg";
    cout << "send second msg: " << sendBuff << endl;
    client->send(sendBuff);
    recvBuff = client->receive();
    if(recvBuff.empty())
    {
        cout << "connection closed" << endl;
        return;
    }
    cout << "received second msg: " << recvBuff << endl;

    recvBuff = client->receive();
    if(!recvBuff.empty())
    {
        cout << "connection not closed" << endl;
        cout << "received data: " << recvBuff << endl;
        client->closeConnection();
        cout << "client closed connection" << endl;
    }
    else
        cout << "connection closed" << endl;
}

int main()
{
    sock::init();
    ClientSockMain();
    sock::cleanup();

    return 0;
}
