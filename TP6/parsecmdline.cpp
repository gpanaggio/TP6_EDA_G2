#include "parsecmdline.h"
#include "structure.h"
#include "simulation_C.h"

int parseCmdLine(int argc, char * argv[], pCallback p, void * userData, simulation_C *sim)
{
	int retValue = NOERROR;
	char * keyword = NULL;
	for (int i = 1; (retValue == NOERROR) && (i < argc); i = i + 2)
	{
		if (argv[i][0] == '-')
			if (argv[i][1] != 0)
				keyword = (char *)argv[i] + 1;
			else
				retValue = ERROR2;

		if (keyword && ((i + 1) == argc))
			retValue = ERROR1;

		if (retValue == NOERROR)
		{
			retValue = (*p)(keyword, (char *)(i + 1 == argc ? argv[i] : argv[i + 1]), userData, simulation_C *sim);
			keyword = NULL;
		}
	}
	if (argc == 1)
		retValue = ERROR3;

	sim->setIP(argv[1]);

	return (retValue);
}