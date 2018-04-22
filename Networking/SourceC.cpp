#include <iostream>
#include "Allegro_c.h"
#include "client_c.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	client_c conquering;
	conquering.startConnection(SERVER_IP);
	conquering.receiveMessage();


	Allegro_c allegro(conquering.getmode());
	allegro.loadBitmap();

	if (!conquering.errorOccurred())
		allegro.run();
	allegro.destroy_all();
}