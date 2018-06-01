//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "SockClientSocket.hpp"
#include "SockSocketUtils.hpp"
#include "SockListeningSocket.hpp"
#include "SockConnection.hpp"

using namespace std;

void ClientConnectionMain()
{
	static const string host = "127.0.0.1";
	static const string port = "1234";
	sock::Data sendBuff;
	sock::Data recvBuff;

	cout << "Create connection to server" << endl;
	sock::Connection conn(host, port);

	sendBuff = "msgToSend 1";
	cout << "Send first msg: " << sendBuff << endl;
	conn.send(sendBuff);

	recvBuff = conn.receive();
	if (recvBuff.empty())
	{
		cout << "Connection closed by server" << endl;
		return;
	}
	cout << "Received first msg: " << recvBuff << endl;

	sendBuff = "msgToSend 2";
	cout << "Send second msg: " << sendBuff << endl;
	conn.send(sendBuff);

	recvBuff = conn.receive();
	if (recvBuff.empty())
	{
		cout << "Connection closed by server" << endl;
		return;
	}
	cout << "Received second msg: " << recvBuff << endl;

	recvBuff = conn.receive();
	if (recvBuff.empty())
	{
		cout << "Connection closed by server" << endl;
		return;
	}
	cout << "Received msg from server: " << recvBuff << endl;
	cout << "Close connection (by destroying connection)" << endl;
}

void ClientSockMain()
{
    static const string host = "127.0.0.1";
    static const string port = "1234";
    sock::Data sendBuff;
    sock::Data recvBuff;
    sock::ClientSocket client;

	cout << "Start connection to server on host: " << host << ", port: " << port << endl;
    client.connect(host, port);

    sendBuff = "first msg";
    cout << "Send first msg: " << sendBuff << endl;
    client.send(sendBuff);
    recvBuff = client.receive();
    cout << "Received first msg: " << recvBuff << endl;

    sendBuff = "secnd msg";
    cout << "Send second msg: " << sendBuff << endl;
    client.send(sendBuff);
    recvBuff = client.receive();
    cout << "Received second msg: " << recvBuff << endl;

    recvBuff = client.receive();
    cout << "Received msg: " << recvBuff << endl;
	cout << "Close connection to server" << endl;
    client.closeConnection();
}

int main()
{
	try
	{
		sock::init();
		//ClientSockMain();
		ClientConnectionMain();
		sock::cleanup();
	}
	catch (exception& e)
	{
		cout << "Error occured. Details: " << e.what() << endl;
	}

    return 0;
}
