#include "parsecallback.h"
#include <string.h>
#include <fwpstypes.h>
#include <stdio.h>

int parseCallback(char *key, char *value, void *userinfo)
{
	using namespace std;

	userData * data = (userData *)userinfo;

	if (key != NULL?(!strcmp(key, "ip")):false)
	{
		data->ip = string(value);
		std::cout << "seteando ip a " << data->ip << endl;
	}
	else if (!strcmp(value, "iniciar"))
	{
		data->iniciar = true;
		std::cout << "setenado inicar a 1" << endl;
	}
	else
	{
		data->invalidData = true;
		cout << "se ha ingresado un parametro invalido" << endl;
	}

	return 1;
}