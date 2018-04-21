#include "client_c.h"


client_c::client_c() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	this->error = false;
}

client_c::~client_c() {
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}

void client_c::startConnection(const char* host) {
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));
	cout << "Trying to connect to " << host << " on port " << HELLO_PORT_STR << std::endl;
	boost::asio::connect(*socket_forClient, endpoint);
	socket_forClient->non_blocking(true);
}

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
		if (!strcmp(buf, "HOMERO") || !strcmp(buf, "HOMER"))										//se que no esta bueno usar un monton de if�s pero no se me ocurre otra
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

mode client_c::getmode()
{
	return modo;
}

bool client_c:: errorOccurred()
{
	return this->error;
}



/*void client_c::receiveMessage() {
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	boost::timer::cpu_timer t;
	t.start();
	boost::timer::cpu_times pastTime = t.elapsed();
	double elapsedSeconds = 0.0;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);		//la linea clave, guardo lo que leo en el buffer, y uso el len para saber cuanto lei

		boost::timer::cpu_times currentTime = t.elapsed();

		if ((currentTime.wall - pastTime.wall) > 1e9)
		{
			elapsedSeconds += (currentTime.wall - pastTime.wall) / 1e9;
			pastTime = currentTime;
			cout << "Pasaron " << elapsedSeconds << " segundos." << endl;
		}

		if (!error)
			buf[len] = '\0';

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
		std::cout << std::endl << "Server sais: " << buf << std::endl;
	else
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}*/