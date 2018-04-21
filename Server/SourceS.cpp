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

	Allegro_C allegro;								//una vez que se conecto empiezo con lo de allegro
	allegro.setmode(BOOM2);
	allegro.loadBitmap();
	allegro.start_timer();
	ALLEGRO_EVENT ev;

	bool next = false;		//con esto indico si termine mi secuencia y le aviso al siguiente	

	while (!next)
	{
		if (al_get_next_event(allegro.get_queue(), &ev))	//tengo el evento registrado en ev
		{
			if (ev.type == ALLEGRO_EVENT_TIMER)		//si tengo un evento de timer...
			{
				next = allegro.update_display();	//cuando termine lo inico con el next
				al_flip_display();
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				next = true;
		}
	}
	allegro.destroy_all();


	conquering.setmode(allegro.getmode());		//le digo al server en que modo estamos
	conquering.sendMessage();			//cuando termine envio el mensaje
	Sleep(50); // Le damos 50ms para que llegue el mensaje antes de cerrar el socket.

	return 0;
}