#pragma once
#include "mode.h"
#include <allegro5/allegro5.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#define FPS	(10.0)
#define FPS_HOMER (1.0/0.1)
#define FPS_MARIO (1.0/0.04)
#define FPS_SONIC (1.0/0.06)
#define FPS_CAT (1.0/0.1)
#define FPS_BOOM1 (1.0/0.12)
#define FPS_BOOM2 (1.0/0.1)

#define VEL_HOMER (100)				//100 px por frame
#define VEL_MARIO (2)
#define VEL_SONIC (70)
#define	VEL_CAT (2)

#define SCREEN_W (1080)
#define SCREEN_H (480)


class Allegro_c
{
public:
	Allegro_c();
	Allegro_c(mode);
	~Allegro_c();
	bool update_display();	//el update devuelve un TRUE cuando se termino la secuencia
	void loadBitmap();
	void start_timer();
	bool draw_next();
	void destroy_all();
	void setmode(mode);
	mode getmode();
	void run();
	ALLEGRO_EVENT_QUEUE	* get_queue();

private:
	ALLEGRO_SAMPLE * music = NULL;
	ALLEGRO_TIMER * timer = NULL;
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE	* queue = NULL;
	ALLEGRO_EVENT ev;
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

