#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#define HELLO_PORT "12345"
#define MAX_IPS 255


class server_C {
public:
	server_C();
	void startConnection();
	void sendMessage();
	char * receiveMessage();	//el recieve ahora nos comunica el mensaje
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);
	~server_C();
	bool errorOccurred();

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	bool error;
	char YOU_GO[MAX_IPS + 2];
	char buf[512];				//el buffer
};

