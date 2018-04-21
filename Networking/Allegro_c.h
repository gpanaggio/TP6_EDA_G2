#pragma once
#include "mode.h"
#include <allegro5/allegro5.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#define FPS (20.0)
#define VEL_HOMER (20)
#define VEL_MARIO (15)
#define VEL_SONIC (30)
#define	VEL_CAT (20)
#define SCREEN_W (1080)
#define SCREEN_H (480)


class Allegro_c
{
public:
	Allegro_c();
	~Allegro_c();
	bool update_display();	//el update devuelve un TRUE cuando se termino la secuencia
	void loadBitmap();
	float getX();
	void start_timer();
	bool draw_next();
	void destroy_all();
	void setmode(mode);
	ALLEGRO_EVENT_QUEUE	* get_queue();

private:
	ALLEGRO_SAMPLE * music = NULL;
	ALLEGRO_TIMER * timer = NULL;
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE	* queue = NULL;
	ALLEGRO_BITMAP ** HomerBitmap = NULL;
	ALLEGRO_BITMAP ** MarioBitmap = NULL;
	ALLEGRO_BITMAP ** SonicBitmap = NULL;
	ALLEGRO_BITMAP ** CatBitmap = NULL;
	ALLEGRO_BITMAP ** Boom1Bitmap = NULL;
	ALLEGRO_BITMAP ** Boom2Bitmap = NULL;
	float coordX;
	float coordY;
	int tick;
	mode modo;
};

