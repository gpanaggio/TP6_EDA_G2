#include <iostream>
#include "client_C.h"
#include "simulation_C.h"

using namespace std;

int main(void)
{
	ParseCmdLine();		//el parse tiene que setear el MustAskUser en TRUE

	simulation_C sim;

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
		if (sim.MustsendMsg)
		{
			client_C * client = new client_C;		//creamos un cliente

		}
	} while (true);
	return 0;
}