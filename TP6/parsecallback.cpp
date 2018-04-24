#include "parsecallback.h"
#include "structure.h"
#include "simulation_C.h"
#include <string.h>

#define MAX_PARAM_SIZE 8

int callback(char * pass, char * value, void * userData, simulation_C * sim)
{
	userInput_t * usr = (userInput_t *)userData;
	int retValue = MYERROR;
	char casehandler[MAX_PARAM_SIZE]; //mayusculas minusculas

	if (pass)
	{
		if ((!(strcmp(strlower(casehandler), "iniciar"))) && !(usr->iniciar))
		{
			sim->SetAskUser();
		}
		else
			retValue = ERROR3;  // This error means that the user used an incorrect keyword
	}
	else
		retValue = ERROR3;

	return  retValue;
}

char* strlower(char str[])
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + ('a' - 'A');
		}
		i++;
	}
	return str;
}