#include <iostream>
#include <string>
#include "client_C.h"
#include "server_C.h"
#include "simulation_C.h"
#include "parsecallback.h"
#include "parsecmd.h"
#include "parsecmd.h"


#define SERVER_IP "localhost"

bool asktoStart();

using namespace std;

int main(int argc, char *argv[])		//CAMBIE DE LUGAR LAS DIRECCIONES
{
	pCallback p = parseCallback;
	userData *  userdata = new userData;

	parseCmdLine(argc, argv, p, (void *)userdata);

	simulation_C * sim = new simulation_C;

	if (userdata->iniciar)
		sim->SetAskUser(true);

	sim->setIP(userdata->ip);

	bool exit = false;
	bool ask = false;
	bool control = false;
	

	do
	{
		
		if (sim->MustAskUser())	//si el MAU esta seteado en TRUE le va a preguntar a usuario
		{
			ask = sim->asktoStart();
			sim->SetAskUser(false);//por si se llama devuelta para que no quede en true
			if (ask)
			{
				sim->requestSeq();
				sim->requestOrder();
			}
			else
			{
				break;
			}

		}
		if (sim->myTurn())
		{
			sim->run();	
		}
		if (sim->MustsendMsg())
		{

			client_C * C = new client_C;		//creamos un cliente
			C->startConnection(/*sim->getnext()*/SERVER_IP, sim->getport());
			
			C->sendMessage(sim->getmsg());
			
			
			delete C;
		}
		if (sim->Imlast())
		{
			sim->SetAskUser(true);
		}
		else
		{
			sim->clearMsg(); //limpio el you_go para que no haya errores al copiar el nuevo mensaje que escucha el servidor
			server_C * S = new server_C;

			S->startConnection();
			sim->newMsg(S->receiveMessage());
			delete S;	//borro el server asi cierro los sockets	
		}
		
	} while (!exit);

	delete userdata;
	delete sim;

	return 0;
}

