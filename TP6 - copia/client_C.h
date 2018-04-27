#pragma once
#include <iostream>
#include <cstdio>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

#define MAX_IPS 255

using namespace std;

class client_C {
public:
	client_C();
	void startConnection(string host, string port);
	void sendMessage(char * msg);
	~client_C();

	bool errorOccurred();

private:
	boost::asio::io_service* IO_handler;		//handler para el sistema operativo
	boost::asio::ip::tcp::socket* socket_forClient;		//socket para la comunicacion
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;		//como el numero de telefono
	bool error;
	char YOU_GO[MAX_IPS + 2];
};
