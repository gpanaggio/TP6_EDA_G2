#include <iostream>
#include <cstdio>
#include "mode.h"
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

#define HELLO_PORT_STR "12345"
#define SERVER_IP "localhost"
#define MAX_IPS 255

using namespace std;

class client_c {
public:
	client_c();
	void startConnection(string host, string port);
	void receiveMessage();
	void sendMessage();
	void setbuffer(char * buff);
	~client_c();
	//void connect(string next_ip, string  )
	
	void setmode(mode);
	mode getmode();
	bool errorOccurred();

private:
	boost::asio::io_service* IO_handler;		//handler para el sistema operativo
	boost::asio::ip::tcp::socket* socket_forClient;		//socket para la comunicacion
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;		//como el numero de telefono
	mode modo;
	bool error;
	char YOU_GO[MAX_IPS+2];
};
