#include <iostream>
#include "modo.h"
#include <cstdio>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#define HELLO_PORT 12345

class server_c {
public:
	server_c();
	void startConnection();
	void sendMessage();
	void receiveMessage();
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);
	~server_c();
	void setmode(mode);
	mode getmode();
	void setbuffer(char * buff);
	bool errorOccurred();

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	mode modo;
	bool error;
};