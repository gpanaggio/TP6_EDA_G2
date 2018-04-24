#include "client_C.h"


client_C::client_C()
{
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	std::cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}


client_C::~client_C()
{
	client_acceptor->close();
	socket_forClient->close();
	delete client_acceptor;
	delete socket_forClient;
	delete IO_handler;
}

void client_C::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void client_C::startConnection() {
	client_acceptor->accept(*socket_forClient);
	socket_forClient->non_blocking(true);
}

void client_C::sendMessage() {
	char buf[512];
	setbuffer(buf);				//seteo en buf el modo en el que estamos

	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forClient->write_some(boost::asio::buffer(buf, strlen(buf)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}

void client_C::setmode(mode modo)
{
	this->modo = modo;
}

void client_C::setbuffer(char * buff)
{
	switch (modo)
	{
	case HOMER:
		strcpy_s(buff, 512, "HOMER");
		break;
	case MARIO:
		strcpy_s(buff, 512, "MARIO");
		break;
	case SONIC:
		strcpy_s(buff, 512, "SONIC");
		break;
	case CAT:
		strcpy_s(buff, 512, "CAT");
		break;
	case BOOM1:
		strcpy_s(buff, 512, "BOOM1");
		break;
	case BOOM2:
		strcpy_s(buff, 512, "BOOM2");
		break;
	default:
		break;
	}
}