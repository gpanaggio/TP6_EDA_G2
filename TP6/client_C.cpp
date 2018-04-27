#include "client_C.h"




client_C::client_C() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	this->error = false;
}


client_C::~client_C() {
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
	

}

void client_C::startConnection(string host, string port) {
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, port));
	cout << "Trying to connect to " << host << " on port " << port << std::endl;
	boost::asio::connect(*socket_forClient, endpoint);
	socket_forClient->non_blocking(true);
}

bool client_C::errorOccurred()
{
	return this->error;
}

void client_C::sendMessage(char * msg)
{
	char buf[512];
	strcpy_s(buf, 512, msg);
								
	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forClient->write_some(boost::asio::buffer(buf, strlen(buf)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}