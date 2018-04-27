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
	cout << "conected" << endl;
	socket_forClient->non_blocking(true);
}
/*
void client_c::receiveMessage() {
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);		//la linea clave, guardo lo que leo en el buffer, y uso el len para saber cuanto lei
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
*/

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