#include "simulation_C.h"
#include <iostream>
#include <string>

using namespace std;


simulation_C::simulation_C()
{
	coordX = 0;
	coordY = SCREEN_H / 3.0;
	tick = 0;
	port = "12345";
	MustAskUse = false;
}


simulation_C::~simulation_C()
{
}

void simulation_C::loadBitmap()
{
	string carpeta;
	string name;
	string bitstr;
	switch (YOU_GO[0])
	{
	case HOMER:
		this->HomerBitmap = new ALLEGRO_BITMAP *[10];
		carpeta = "Homer Dance/";
		name = "homerdance-F";
		for (int i = 0; i < 10; i++)
		{
			bitstr = carpeta + name + to_string(i + 1) + ".png";	//tengo en image la sentencia de cada imagen
			this->HomerBitmap[i] = al_load_bitmap(bitstr.c_str());	//cargo en el arreglo de bitmaps los homerbits //image[i].c_str()
		}
		break;
	case MARIO:
		this->MarioBitmap = new ALLEGRO_BITMAP *[12];
		carpeta = "Super Mario/";
		name = "Super Mario Running-F";
		for (int i = 0; i < 12; i++)
		{
			bitstr = carpeta + name + to_string(i + 1) + ".png";
			this->MarioBitmap[i] = al_load_bitmap(bitstr.c_str());
		}
		break;
	case SONIC:
		this->SonicBitmap = new ALLEGRO_BITMAP *[10];
		carpeta = "Sonic/";
		name = "Sonic Running-F";
		for (int i = 0; i < 10; i++)
		{
			bitstr = carpeta + name + to_string(i + 1) + ".png";
			this->SonicBitmap[i] = al_load_bitmap(bitstr.c_str());
		}
		break;
	case CAT:
		this->CatBitmap = new ALLEGRO_BITMAP *[12];
		carpeta = "Cat Running/";
		name = "Cat Running-F";
		for (int i = 0; i < 12; i++)
		{
			bitstr = carpeta + name + to_string(i + 1) + ".png";
			this->CatBitmap[i] = al_load_bitmap(bitstr.c_str());
		}
		break;
	case BOOM1:
		this->Boom1Bitmap = new ALLEGRO_BITMAP *[8];
		carpeta = "Explosion 1/";
		name = "Explosion 1-F";
		for (int i = 0; i < 7; i++)
		{
			bitstr = carpeta + name + to_string(i + 1) + ".png";
			this->Boom1Bitmap[i] = al_load_bitmap(bitstr.c_str());
		}
		break;
	case BOOM2:
		this->Boom2Bitmap = new ALLEGRO_BITMAP *[48];
		carpeta = "Explosion 2/";
		name = "Explosion 2-F";
		for (int i = 0; i < 47; i++)
		{
			bitstr = carpeta + name + to_string(i + 1) + ".png";
			this->Boom2Bitmap[i] = al_load_bitmap(bitstr.c_str());
		}
		break;
	}
}

void simulation_C::destroy_all()
{
	al_destroy_display(display);	//destruyo todo
	al_stop_samples();
	al_destroy_sample(music);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_shutdown_image_addon();
	al_uninstall_audio();
	switch (tolower(YOU_GO[0]))
	{
	case HOMER:
		delete[] HomerBitmap;
		break;
	case MARIO:
		delete[] MarioBitmap;
		break;
	case SONIC:
		delete[] SonicBitmap;
		break;
	case CAT:
		delete[] CatBitmap;
		break;
	case BOOM1:
		delete[] Boom1Bitmap;
		break;
	case BOOM2:
		delete[] Boom2Bitmap;
		break;
	}
}


void simulation_C::create_all()
{
	if (al_init())	//inicializo allegro
	{
		if (al_install_audio())	//inicializo los audios
		{
			if (al_init_acodec_addon())
			{
				if ((al_reserve_samples(1)))	//para la musica
				{
					if (al_init_image_addon())	//addon para las imagenes
					{
						if (al_install_keyboard())	//inicializo para que lea teclado
						{
							if ((queue = al_create_event_queue()))	//creo la cola de eventos
							{
								if ((display = al_create_display(SCREEN_W, SCREEN_H)))	//creo el display
								{
									al_register_event_source(this->queue, al_get_keyboard_event_source());	//hago que la cola de eventos registre el teclado
									al_register_event_source(this->queue, al_get_display_event_source(this->display));	//que registre cosas del display
																														//al_register_event_source(this->queue, al_get_timer_event_source(this->timer));	//y del timer
								}
							}
						}
					}
					else
						fprintf(stderr, "ERROR: Failed to load Image addon\n");
				}
				else
					fprintf(stderr, "ERROR: Failed to reserve sample\n");
			}
			else
				fprintf(stderr, "ERROR: Failed to install acodec addon\n");
		}
		else
			fprintf(stderr, "ERROR: Failed to install audio\n");
	}
	else
		fprintf(stderr, "ERROR: Failed to initialize allegro system\n");
}

void simulation_C::setmode(mode modo)
{
	this->modo = modo;
}

mode simulation_C::getmode()
{
	return this->modo;
}

void simulation_C::run()
{
	create_all();


	coordX = 0;
	tick = 0;
	coordY = SCREEN_H / 3.0;
	bool next = false;		//con esto indico si termine mi secuencia y le aviso al siguiente	
	loadBitmap();
	draw();
	destroy_all();

	(YOU_GO[1])++;		//incremento el count
}

bool simulation_C::MustAskUser()
{
	return MustAskUse;
}

void simulation_C::requestSeq()
{
	std::cout << "Please enter the animation" << std::endl;
	std::cout << "You can choose from:" << std::endl;
	std::cout << "A.Cat" << std::endl;
	std::cout << "B.Awesome explosion" << std::endl;
	std::cout << "C.Cool explosion" << std::endl;
	std::cout << "D.Dancing Homer" << std::endl;
	std::cout << "E.Mario Bros" << std::endl;
	std::cout << "F.Sonic" << std::endl;
	char c;
	do {
		c = getchar();
		do
		{
		} while (getchar() != '\n');	//limpio el buffer que que no considere el entre key
		if (tolower(c)<'a' || tolower(c)>'f')
			std::cout << "invalid input, enter from 'A' to 'F'" << std::endl;
	} while (tolower(c)<'a' || tolower(c)>'f');

	YOU_GO[0] = tolower(c);		//tengo en el primer casillero del paquete la animacion que quiero (A, B, etc...)
	
	YOU_GO[1] = 1;		//como soy el primero seteo el count en 1
}

void simulation_C::requestOrder()
{
	using namespace std;
	cout << "Choose now the sequence in which you want see the animation." << endl;
	cout << "To do that write a number follow by a space and after you finish writing the sequence press space." << endl;
	cout << "It will only accept numbers from 1 to 255." << endl;
	bool exit = false;
	while (!exit)
	{
		std::string newInput = "";
		std::string input = "";
		std::getline(cin, input);
		std::stringstream ss(input);
		int numeros[255];
		int num = 0;
		int cont = 0;
		bool restart = false;
		while (std::getline(ss, input, ' '))
		{

			if ((input == "\n") || restart)
			{
				break;
			}
			else
			{
				if (input.length() > 0)
				{

					num = atoi(input.c_str());
					if ((num >= 1) && (num <= 255))
					{
						numeros[cont] = num;
						cont++;
						restart = false;
					}
					else
					{
						restart = true;
					}
				}
			}

		}
		if (!restart)
		{
			for (int i = 0; i < cont; i++)
			{
				YOU_GO[i + 2] = numeros[i];
			}
			exit = true;
		}
		else if (restart)
		{
			cout << "Wrong input please enter the whole sequence again with a number from 1 to 255 follow by an space" << endl;
		}
	}
	//NO OLVIDAR QUE LUEGO DE LA SECUENCIA HAY QUE PONER EL TERMINADOR
}

bool simulation_C::myTurn()
{
	bool myturn = false;
	ifstream src("direcciones.txt");
	int count = (int)(YOU_GO[1]);
	int n = 1;
	string line;

	while (src.good())
	{
		getline(src, line);
		if (n == YOU_GO[1 + count])		//nos ubicamos en la linea indicada segun el count
		{
			if (!strcmp(line.c_str(), my_ip.c_str()))	//si las ip´s coinciden se que es mi turno
				myturn = true;
		}
		n++;
	}

	return myturn;
}

bool simulation_C::MustsendMsg()
{
	bool mustsendmsg = true;
	int n = ((int)YOU_GO[1]);	//hago un casteo explicito del count
	if (YOU_GO[n + 1] == '\0')		//me fijo si despues de mi no viene nadie (el string termina)
	{
		mustsendmsg = false;
	}
	return mustsendmsg;
}

string simulation_C::getnext()
{
	ifstream src("direcciones.txt");
	unsigned int n = 1;
	unsigned int count = (unsigned int)(YOU_GO[1]);				//tengo en la variable count donde esta el que sigue
	unsigned int next = (unsigned int)(YOU_GO[count + 1]);		//en next tengo la maquina que sigue
	string line;

	while (src.good())
	{
		getline(src, line);
		if (n == next)		//me paro en la linea del txt de el que sigue
		{
			return line;
		}
		n++;
	}
}

string simulation_C::getport()
{
	return port;
}

char * simulation_C::getmsg()
{
	return YOU_GO;
}

void simulation_C::SetAskUser(bool answer)
{
	MustAskUse =answer;
}

void simulation_C::setIP(string ip)
{
	my_ip = ip;
}

void simulation_C::newMsg(char * msg)
{
	strcpy_s(YOU_GO, 257, msg);
}

void simulation_C::clearMsg()
{
	for (int i = 0; i < MAX_IPs + 2; i++)
	{
		YOU_GO[i] = '\0';
	}
}





void simulation_C::draw()
{
	bool finished = false;
	switch (tolower(YOU_GO[0]))
	{
	
		case HOMER:
			while (coordX < SCREEN_W)
			{
				coordX += VEL_HOMER;
				tick == 9 ? tick = 0 : tick++;
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_bitmap(HomerBitmap[tick], coordX, coordY, 0);
				al_flip_display();
				al_rest(FPS_HOMER);
				
			}
			break;
		case MARIO:
			while (coordX < SCREEN_W)
			{
				coordX += VEL_MARIO;
				tick == 11 ? tick = 0 : tick++;
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_scaled_bitmap(MarioBitmap[tick], 0, 0, al_get_bitmap_width(MarioBitmap[tick]), al_get_bitmap_height(MarioBitmap[tick]), coordX, coordY, al_get_bitmap_width(MarioBitmap[tick]) / 2, al_get_bitmap_height(MarioBitmap[tick]) / 2, 0);
				al_flip_display();
				al_rest(FPS_MARIO);

			}
			break;
		case CAT:
			while (coordX < SCREEN_W)
			{
				coordX += VEL_CAT;
				tick == 11 ? tick = 0 : tick++;
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_scaled_bitmap(CatBitmap[tick], 0, 0, al_get_bitmap_width(CatBitmap[tick]), al_get_bitmap_height(CatBitmap[tick]), coordX, coordY, al_get_bitmap_width(CatBitmap[tick]) / 2, al_get_bitmap_height(CatBitmap[tick]) / 2, 0);
				al_flip_display();
				al_rest(FPS_CAT);

			}
			break;
		case SONIC:
			while (coordX < SCREEN_W)
			{
				(tick == 0 || tick == 4) ? coordX += VEL_SONIC : NULL;
				tick == 9 ? tick = 0 : tick++;
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_scaled_bitmap(SonicBitmap[tick], 0, 0, al_get_bitmap_width(SonicBitmap[tick]), al_get_bitmap_height(SonicBitmap[tick]), /*SCREEN_W -*/ coordX, coordY, al_get_bitmap_width(SonicBitmap[tick]) / 2, al_get_bitmap_height(SonicBitmap[tick]) / 2, ALLEGRO_FLIP_HORIZONTAL);
				al_flip_display();
				al_rest(FPS_SONIC);

			}
			break;
		case BOOM1:
			
			while (!finished)
			{
				tick == 6 ? finished = true : tick++;
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(Boom1Bitmap[tick], al_get_display_width(display) / 2 - al_get_bitmap_width(Boom1Bitmap[tick]) / 2, al_get_display_height(display) / 2 - al_get_bitmap_height(Boom1Bitmap[tick]) / 2, 0);
				al_flip_display();
				al_rest(FPS_BOOM1);
			}
			break;
		case BOOM2:
			
			while (!finished)
			{
				tick == 46 ? finished = true : tick++;
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(Boom2Bitmap[tick], al_get_display_width(display) / 2 - al_get_bitmap_width(Boom2Bitmap[tick]) / 2, al_get_display_height(display) / 2 - al_get_bitmap_height(Boom2Bitmap[tick]) / 2, 0);
				al_flip_display();
				al_rest( FPS_BOOM2);

			}
			break;
		
		
	}
}






bool simulation_C::asktoStart()
{
	cout << "Do you want to send an animation?" << endl;
	cout << "Press 'Y' then enter for yes or press 'N' then enter for no" << endl;
	bool init = true;
	char c;
	bool keepOpen = false;
	while (init)
	{
		while ((c = getchar()) != '\n')
		{
			if (tolower(c) == 'y')
			{
				init = false;
				keepOpen = true;
			}
			else if (tolower(c))
			{
				init = false;
				keepOpen = false;
				cout << "Closing all" << endl;
				cout << "See you in space cowboy" << endl;
			}
			else
			{
				cout << "Wrong input. Please press 'Y' for yes or 'N' for no." << endl;
			}
		}
	}
	return keepOpen;
}
