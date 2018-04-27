#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

void main()
{
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	boost::asio::ip::tcp::socket* socket_forClient;		//socket para la comunicacion
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;

	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));
	std::cout << std::endl << "Ready. Port " << 12345 << " created" << std::endl;
	server_acceptor->accept(*(socket_forServer));
	//socket_forServer->non_blocking(true);
	std::cout << "recibi mensaje" << std::endl;

	getchar();
	socket_forServer->close();
	delete server_acceptor;

	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query("localhost", "12345"));
	std::cout << "Trying to connect to " << "localhost" << " on port " << 12345 << std::endl;
	boost::system::error_code code;
	boost::asio::connect(*socket_forClient, endpoint,code);

	getchar();
	socket_forClient->close();

	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query("localhost", "12345"));
	std::cout << "Trying to connect to " << "localhost" << " on port " << 12345 << std::endl;
	boost::asio::connect(*socket_forClient, endpoint, code);
	getchar();
}