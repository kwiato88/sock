//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include <iostream>
#include <string>
#include <memory>
#include "SockListeningSocket.hpp"
#include "SockSocketUtils.hpp"
#include "SockClientSocket.hpp"
#include "SockServer.hpp"

using namespace std;

void ServerConnectionMain()
{
	static const string host = "127.0.0.1";
	static const string port = "1234";
	sock::Data sendBuff;
	sock::Data recvBuff;

	cout << "Setup server on host: " << host << ", port: " << port << endl;
	sock::Server ser(host, port);

	cout << "Start accepting connections" << endl;
	auto conn(ser.accept());
	cout << "Connection accepted" << endl;

	recvBuff = conn->receive();
	cout << "Received first msg: " << recvBuff << endl;

	sendBuff = recvBuff;
	sendBuff += " OK";
	cout << "Send response: " << sendBuff << endl;
	conn->send(sendBuff);

	recvBuff = conn->receive();
	cout << "Received second msg: " << recvBuff << endl;
	sendBuff = recvBuff;
	sendBuff += " OK";
	cout << "Send response: " << sendBuff << endl;
	conn->send(sendBuff);

	cout << "Close connection (by destroying connection)" << endl;
}

void SerwerSockMain()
{
    static const string host = "127.0.0.1";
    static const string port = "1234";
    sock::Data sendBuff;
    sock::Data recvBuff;
    sock::ListeningSocket listener;

	cout << "Setup server on host: " << host << ", port: " << port << endl;
    listener.bind(host, port);
    listener.listen();

	cout << "Start accepting connections" << endl;
    auto client(listener.accept());
	cout << "Connection accepted" << endl;

    recvBuff = client->receive();
    cout << "Received first msg: " << recvBuff << endl;
    sendBuff = recvBuff;
    sendBuff += " OK";
    cout << "Send response: " << sendBuff << endl;
	client->send(sendBuff);
	
    recvBuff = client->receive();
    cout << "Received second msg: " << recvBuff << endl;
    sendBuff = recvBuff;
    sendBuff += " OK";
    cout << "Send response: " << sendBuff << endl;
    client->send(sendBuff);

	cout << "Close connection" << endl;
    client->closeConnection();
}

int main()
{
	try
	{
		sock::init();
		//SerwerSockMain();
		ServerConnectionMain();
		sock::cleanup();
	}
	catch (exception& e)
	{
		cout << "Error occured. Deatils: " << e.what() << endl;
	}

    return 0;
}
