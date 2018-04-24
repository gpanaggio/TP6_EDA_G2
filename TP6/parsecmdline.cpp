#include "parsecmdline.h"
#include "structure.h"
#include "simulation_C.h"

int parseCmdLine(int argc, char * argv[], pCallback p, void * userData, simulation_C *sim)
{
	int retValue = MYERROR;
	char * keyword = NULL;
	for (int i = 1; (retValue == MYERROR) && (i < argc); i = i + 2)
	{
		if (argv[i][0] == '-')								//verifica si es error2
			if (argv[i][1] != 0)
				keyword = (char *)argv[i] + 1;
			else
				retValue = ERROR2;

		if (keyword && ((i + 1) == argc))					//verifica error1
			retValue = ERROR1;

		if (retValue == MYERROR)							//Uso el callback si no se produjo ningun error
		{
			retValue = (*p)(keyword, (char *)(i + 1 == argc ? argv[i] : argv[i + 1]), userData, sim);
			keyword = NULL;
		}
	}
	if (argc == 1)
		retValue = ERROR3;

	sim->setIP(argv[1]);

	return (retValue);
}