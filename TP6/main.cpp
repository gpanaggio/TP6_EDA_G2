#include <iostream>
#include "client_C.h"
#include "server_C.h"
#include "simulation_C.h"
#include "parsecallback.h"
#include "parsecmd.h"
#include "parsecmd.h"

using namespace std;

int main(int argc, char *argv[])
{
	pCallback p = parseCallback;
	userData *  userdata = new userData;

	parseCmdLine(argc, argv, p, (void *)userdata);

	simulation_C * sim = new simulation_C;

	if (userdata->iniciar)
		sim->SetAskUser();

	sim.setIP(userdata->ip);

	bool exit = false;

	do
	{
		if (sim->MustAskUser())	//el el MAU esta seteado en TRUE le va a preguntar a usuario
		{
			sim->requestSeq();
			sim->requestOrder();
		}
		if (sim->myTurn())
		{
			sim->run();
			
		}
		if (sim->MustsendMsg())
		{
			client_C * C = new client_C;		//creamos un cliente
			C->startConnection(sim->getnext(), sim->getport());
			C->sendMessage(sim->getmsg());
			delete C;
		}
		else
			exit = true;
		server_C * S = new server_C;
		S->startConnection();
		sim->newMsg(S->receiveMessage());
	} while (!exit);

	delete userdata;
	delete sim;

	return 0;
}