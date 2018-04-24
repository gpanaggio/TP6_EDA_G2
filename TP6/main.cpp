#include <iostream>
#include "pCallback.h"
#include "client_C.h"
#include "server_C.h"
#include "simulation_C.h"

using namespace std;

int main(int argc, char ** argv)
{
	simulation_C sim;

	ParseCmdLine(argc, argv, &sim);		//el parse tiene que setear el MustAskUser en TRUE

	bool exit = false;

	do
	{
		if (sim.MustAskUser())	//el el MAU esta seteado en TRUE le va a preguntar a usuario
		{
			sim.requestSeq();
			sim.requestOrder();
		}
		if (sim.myTurn())
		{
			sim.run();
			
		}
		if (sim.MustsendMsg())
		{
			client_C * C = new client_C;		//creamos un cliente
			C->startConnection(sim.getnext(), sim.getport());
			C->sendMessage(sim.getmsg());
			delete C;
		}
		else
			exit = true;
		server_C * S = new server_C;
		S->startConnection();
		sim.newMsg(S->receiveMessage());
	} while (true);
	return 0;
}