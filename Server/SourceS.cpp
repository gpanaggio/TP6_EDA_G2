#include <iostream>
#include "Allegro_C.h"
#include "server_c.h"


int main(int argc, char* argv[])
{
	server_c conquering;							//creamos el server
	std::cout << "iniciando conexion" << std::endl;
	conquering.startConnection();					//comienzo la conexion
	std::cout << "presione enter para comenzar" << std::endl;
	getchar();

	Allegro_C allegro(MARIO);								//una vez que se conecto empiezo con lo de allegro
	allegro.loadBitmap();
	allegro.run();
	allegro.destroy_all();


	conquering.setmode(allegro.getmode());		//le digo al server en que modo estamos
	conquering.sendMessage();			//cuando termine envio el mensaje
	Sleep(50); // Le damos 50ms para que llegue el mensaje antes de cerrar el socket.

	return 0;
}}