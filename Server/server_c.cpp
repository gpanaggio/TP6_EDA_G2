#include "server_c.h"



server_c::server_c()
{
	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	std::cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}


server_c::~server_c()
{
	server_acceptor->close();
	socket_forServer->close();
	delete server_acceptor;
	delete socket_forServer;
	delete IO_handler;
}

void server_c::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void server_c::startConnection() {
	server_acceptor->accept(*socket_forServer);
	socket_forServer->non_blocking(true);
}

void server_c::sendMessage() {
	char buf[512];
	setbuffer(buf);				//seteo en buf el modo en el que estamos

	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forServer->write_some(boost::asio::buffer(buf, strlen(buf)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}

/*
void server_c::sendMessage() {
char buf[512] = "your turn.";		//le digo al siguente que es su turno

size_t len;
boost::system::error_code error;

do
{
len = socket_forServer->write_some(boost::asio::buffer(buf, strlen(buf)), error);
} while ((error.value() == WSAEWOULDBLOCK));
if (error)
std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}
*/						/*REPUESTO*/



void server_c::setmode(mode modo)
{
	this->modo = modo;
}

void server_c::setbuffer(char * buff)
{
	switch (modo)
	{
	case HOMER:
		strcpy_s(buff, 512,"HOMER");
		break;
	case MARIO:
		strcpy_s(buff, 512,"MARIO");
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