#include <iostream>
#include "Allegro_c.h"
#include "client_c.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	client_c conquering;
	conquering.startConnection(SERVER_IP);
	std::cout << "presione enter para mandar homero" << std::endl;
	int c =getchar();
	mode test;
	switch (c)
	{
	case '0':
		test=HOMER;
		break;
	case '1':
		test = MARIO;
		break;
	case '2':
		test = SONIC;
		break;
	case '3':
		test = CAT;
		break;
	case '4':
		test = BOOM1;
		break;
	case '5':
		test = BOOM2;
		break;
	default:
		test = HOMER;
		break;
	}
	
	Allegro_c allegro(test);								//una vez que se conecto empiezo con lo de allegro
	allegro.loadBitmap();
	allegro.run();
	allegro.destroy_all();


	conquering.setmode(allegro.getmode());		//le digo al server en que modo estamos
	conquering.sendMessage();			//cuando termine envio el mensaje
	Sleep(50); // Le damos 50ms para que llegue el mensaje antes de cerrar el socket.
	
	/*

	conquering.receiveMessage();
	Allegro_c allegro(conquering.getmode());
	allegro.loadBitmap();

	if (!conquering.errorOccurred())
		allegro.run();
	allegro.destroy_all();
	*/
	

	
}