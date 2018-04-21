#include <iostream>
#include "Allegro_c.h"
#include "client_c.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	client_c conquering;
	conquering.startConnection(SERVER_IP);
	conquering.receiveMessage();


	Allegro_c allegro;
	allegro.setmode(conquering.getmode());
	allegro.loadBitmap();
	allegro.start_timer();
	ALLEGRO_EVENT ev;

	bool next = false;		//con esto indico si termine mi secuencia y le aviso al siguiente	

	if(!conquering.errorOccurred())
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
}