#include "Allegro_c.h"
#include <iostream>
#include <string>

using namespace std;


Allegro_C::Allegro_C()
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
								if ((timer = al_create_timer(1 / FPS)))	//creo el timer
								{
									if ((display = al_create_display(SCREEN_W, SCREEN_H)))	//creo el display
									{

										al_register_event_source(this->queue, al_get_keyboard_event_source());	//hago que la cola de eventos registre el teclado
										al_register_event_source(this->queue, al_get_display_event_source(this->display));	//que registre cosas del display
										al_register_event_source(this->queue, al_get_timer_event_source(this->timer));	//y del timer
									}
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

	coordX = 0;
	coordY = SCREEN_H / 3.0;
	tick = 0;
}


Allegro_C::Allegro_C(mode modo)
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
								switch (modo)
								{
								case HOMER:
									if ((timer = al_create_timer(1 / FPS_HOMER))) {}
									break;
								case MARIO:
									if ((timer = al_create_timer(1 / FPS_MARIO))) {}
									break;
								case SONIC:
									if ((timer = al_create_timer(1 / FPS_SONIC))) {}
									break;
								case CAT:
									if ((timer = al_create_timer(1 / FPS_CAT))) {}
									break;
								case BOOM1:
									if ((timer = al_create_timer(1 / FPS_BOOM1))) {}
									break;
								case BOOM2:
									if ((timer = al_create_timer(1 / FPS_BOOM2))) {}
									break;
								}
								if ((display = al_create_display(SCREEN_W, SCREEN_H)))	//creo el display
								{

									al_register_event_source(this->queue, al_get_keyboard_event_source());	//hago que la cola de eventos registre el teclado
									al_register_event_source(this->queue, al_get_display_event_source(this->display));	//que registre cosas del display
									al_register_event_source(this->queue, al_get_timer_event_source(this->timer));	//y del timer
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

	coordX = 0;
	coordY = SCREEN_H / 3.0;
	tick = 0;
	this->modo = modo;
}



Allegro_C::~Allegro_C()
{
}

bool Allegro_C::update_display()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	return draw_next();
}

void Allegro_C::loadBitmap()
{
	string carpeta;
	string name;
	string bitstr;
	switch (modo)
	{
	case HOMER:
	HOMER:
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

ALLEGRO_EVENT_QUEUE * Allegro_C::get_queue()
{
	return queue;
}

void Allegro_C::start_timer()
{
	al_start_timer(timer);
}

bool Allegro_C::draw_next()
{
	bool reach_end = false;

	switch (modo)
	{
	case HOMER:
		(coordX > SCREEN_W) ? reach_end = true : coordX += VEL_HOMER;		//si llego al final le aviso
		tick == 9 ? tick = 0 : tick++;
		al_draw_bitmap(HomerBitmap[tick], coordX, coordY, 0);
		break;
	case MARIO:
		(coordX > SCREEN_W) ? reach_end = true : coordX += VEL_MARIO;
		tick == 11 ? tick = 0 : tick++;
		al_draw_scaled_bitmap(MarioBitmap[tick], 0, 0, al_get_bitmap_width(MarioBitmap[tick]), al_get_bitmap_height(MarioBitmap[tick]), coordX, coordY, al_get_bitmap_width(MarioBitmap[tick]) / 2, al_get_bitmap_height(MarioBitmap[tick]) / 2, 0);
		break;
	case SONIC:
		(coordX > SCREEN_W) ? reach_end = true : NULL;
		(tick == 0 || tick == 4) ? coordX += VEL_SONIC : NULL;
		tick == 9 ? tick = 0 : tick++;
		al_draw_scaled_bitmap(SonicBitmap[tick], 0, 0, al_get_bitmap_width(SonicBitmap[tick]), al_get_bitmap_height(SonicBitmap[tick]), SCREEN_W - coordX, coordY, al_get_bitmap_width(SonicBitmap[tick]) / 2, al_get_bitmap_height(SonicBitmap[tick]) / 2, 0);
		break;
	case CAT:
		(coordX > SCREEN_W) ? reach_end = true : coordX += VEL_CAT;
		tick == 11 ? tick = 0 : tick++;
		al_draw_scaled_bitmap(CatBitmap[tick], 0, 0, al_get_bitmap_width(CatBitmap[tick]), al_get_bitmap_height(CatBitmap[tick]), coordX, coordY, al_get_bitmap_width(CatBitmap[tick]) / 2, al_get_bitmap_height(CatBitmap[tick]) / 2, 0);
		break;
	case BOOM1:
		tick == 6 ? reach_end = true : tick++;
		al_draw_bitmap(Boom1Bitmap[tick], al_get_display_width(display) / 2 - al_get_bitmap_width(Boom1Bitmap[tick]) / 2, al_get_display_height(display) / 2 - al_get_bitmap_height(Boom1Bitmap[tick]) / 2, 0);
		break;

	case BOOM2:
		tick == 46 ? reach_end = true : tick++;
		al_draw_bitmap(Boom2Bitmap[tick], al_get_display_width(display) / 2 - al_get_bitmap_width(Boom2Bitmap[tick]) / 2, al_get_display_height(display) / 2 - al_get_bitmap_height(Boom2Bitmap[tick]) / 2, 0);
		break;
	}

	return reach_end;
}


void Allegro_C::destroy_all()
{
	al_destroy_display(display);	//destruyo todo
	al_stop_samples();
	al_destroy_sample(music);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_shutdown_image_addon();
	al_uninstall_audio();
	switch (modo)
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

void Allegro_C::setmode(mode modo)
{
	this->modo = modo;
}

mode Allegro_C::getmode()
{
	return this->modo;
}

void Allegro_C::run()
{
	bool next = false;		//con esto indico si termine mi secuencia y le aviso al siguiente	
	start_timer();

	while (!next)
	{
		if (al_get_next_event(queue, &ev))	//tengo el evento registrado en ev
		{
			if (ev.type == ALLEGRO_EVENT_TIMER)		//si tengo un evento de timer...
			{
				next = update_display();	//cuando termine lo inico con el next
				al_flip_display();
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				next = true;
		}
	}
}