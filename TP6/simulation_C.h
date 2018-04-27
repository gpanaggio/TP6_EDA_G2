#pragma once
#include "mod.h"
#include <string>
#include <fstream>
#include <sstream>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#define FPS	(10.0)
#define FPS_HOMER (1.0/10.0)
#define FPS_MARIO (1.0/25.0)
#define FPS_SONIC (1.0/(50.0/3.0))
#define FPS_CAT (1.0/10.0)
#define FPS_BOOM1 (1.0/(25.0/3.0))
#define FPS_BOOM2 (1.0/10.0)

#define VEL_HOMER (100)				//100 px por frame
#define VEL_MARIO (2)
#define VEL_SONIC (70)
#define	VEL_CAT (2)

#define SCREEN_W (1080)
#define SCREEN_H (480)

#define MAX_IPs (255)

using namespace std;

class simulation_C
{
public:
	simulation_C();
	~simulation_C();
	
	// funciones de allegro
	void loadBitmap();
	void create_all();
	void destroy_all();
	void draw();
	//termina funciones de allegro
	void setmode(mode);
	mode getmode();
	void run();
	void SetAskUser(bool);
	bool MustAskUser();
	void requestSeq();
	void requestOrder();	//LOS GUARDO EN EL YOU_GO
	bool myTurn();
	bool MustsendMsg();
	string getnext();	//devuelve un string con la direccion ip de que sigue
	string getport();
	char * getmsg();
	void setIP(string);
	void newMsg(char *);
	void clearMsg();
	bool asktoStart();

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
	bool MustAskUse;		//usamos esta variable para saber si esta es la maquina que tiene que hablar con el user
	char YOU_GO[MAX_IPs + 2];			//tendremos que hacerle una malloc para guardar memoria, o un YOU_GO = new char[257] ?
	string port;			//el puerto al que escuchamos
	string my_ip;

};