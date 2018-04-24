#include "server_C.h"


server_C::server_C() {
	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	this->error = false;
}

server_C::~server_C() {
	socket_forServer->close();
	delete server_resolver;
	delete socket_forServer;
	delete IO_handler;
}

void server_C::startConnection(const char* host) {
	endpoint = server_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));
	cout << "Trying to connect to " << host << " on port " << HELLO_PORT_STR << std::endl;
	boost::asio::connect(*socket_forServer, endpoint);
	socket_forServer->non_blocking(true);
}

void server_C::receiveMessage() {
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	do
	{
		len = socket_forServer->read_some(boost::asio::buffer(buf), error);		//la linea clave, guardo lo que leo en el buffer, y uso el len para saber cuanto lei
		if (!error)
			buf[len] = '\0';

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
	{
		std::cout << std::endl << "Server sais: " << buf << std::endl;
		if (!strcmp(buf, "HOMERO") || !strcmp(buf, "HOMER"))										//se que no esta bueno usar un monton de if´s pero no se me ocurre otra
			modo = HOMER;
		else if (!strcmp(buf, "MARIO"))
			modo = MARIO;
		else if (!strcmp(buf, "SONIC"))
			modo = SONIC;
		else if (!strcmp(buf, "CAT"))
			modo = CAT;
		else if (!strcmp(buf, "BOOM1"))
			modo = BOOM1;
		else if (!strcmp(buf, "BOOM2"))
			modo = BOOM2;
	}
	else
	{
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		this->error = true;
	}
}

mode server_C::getmode()
{
	return modo;
}

bool server_C::errorOccurred()
{
	return this->error;
}


