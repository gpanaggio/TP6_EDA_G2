#include <iostream>
#include "client_C.h"
#include "server_C.h"
#include "simulation_C.h"
#include "structure.h"
#include "parsecallback.h"
#include "parsecmdline.h"

using namespace std;

int main(int argc, char *argv[])
{

	userInput_t userData = { 0 };

	simulation_C sim;

	switch (parseCmdLine(argc, argv, &callback, &userData, &sim))
	{
	case ERROR1:
		printf("Error type 1\n");
		while (getchar() != '\n');	//Afrefo asi no desaparece la consola
		return 0;
	case ERROR2:
		printf("Error type 2\n");
		while (getchar() != '\n');
		return 0;
	case ERROR3:
		printf("Error type 3\n");
		while (getchar() != '\n');
		return 0;
	}

	simulation_C sim;

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
	} while (!exit);
	return 0;
}