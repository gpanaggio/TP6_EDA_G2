#include <iostream>
#include "Allegro_c.h"
#include "client_c.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	client_c conquering;
	conquering.startConnection(SERVER_IP);
	std::cout << "presione enter para mandar homero" << std::endl;
	getchar();
	
	Allegro_c allegro(HOMER);								//una vez que se conecto empiezo con lo de allegro
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