#include <iostream>
#include "mod.h"
#include <cstdio>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#define HELLO_PORT 50013

class client_C
{
public:
	client_C();
	void startConnection();
	void sendMessage();
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);
	~client_C();
	void setmode(mode);
	void setbuffer(char * buff);

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::acceptor* client_acceptor;
	mode modo;
};

