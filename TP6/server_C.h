#include <iostream>
#include <cstdio>
#include "mod.h"
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

#define HELLO_PORT_STR "50013"
#define SERVER_IP "localhost"


using namespace std;

class server_C
{
public:
	server_C();
	void startConnection(const char* host);
	void receiveMessage();
	~server_C();
	mode getmode();
	bool errorOccurred();

private:
	boost::asio::io_service* IO_handler;		//handler para el sistema operativo
	boost::asio::ip::tcp::socket* socket_forServer;		//socket para la comunicacion
	boost::asio::ip::tcp::resolver* server_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;		//como el numero de telefono
	mode modo;
	bool error;
};

