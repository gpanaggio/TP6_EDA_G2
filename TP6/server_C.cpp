#include "server_C.h"
using namespace std;


server_C::server_C()
{

	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), stoi(HELLO_PORT)));
	std::cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}


server_C::~server_C()
{
	server_acceptor->close();
	socket_forServer->close();
	delete server_acceptor;
	delete socket_forServer;
	delete IO_handler;

}

void server_C::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void server_C::startConnection() {
	server_acceptor->accept(*socket_forServer);
	//socket_forServer->non_blocking(true);
}

void server_C::sendMessage() {
	char buff[512];
	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forServer->write_some(boost::asio::buffer(buff, strlen(buff)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}

bool server_C::errorOccurred()
{
	return this->error;
}

char * server_C::receiveMessage() {
	boost::system::error_code error;
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	do
	{
		len = socket_forServer->read_some(boost::asio::buffer(buf), error);		//la linea clave, guardo lo que leo en el buffer, y uso el len para saber cuanto lei


	} while (error.value() == WSAEWOULDBLOCK);
	if (!error)
		buf[len] = '\0';

	if (!error)
	{
		std::cout << std::endl << "Server sais: " << buf << std::endl;
		return buf;
	}
	else
	{
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		this->error = true;
		return NULL;
	}
}