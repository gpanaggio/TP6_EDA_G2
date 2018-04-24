
#include "parsecmd.h"
#include "parsecallback.h"

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData) {
	int final = 0, result = 0, posible = 0, error = false;

	for (int i = 1; i<argc;) {
		if (argv[i][0] == '-') { //Si el primer caracter es un - sera una opcion (opcion es clave+valor)
			if (argv[i][1] == 0) //si pasan -  solo
			{
				error = ERROR2;
				i = argc;
			}
			else if ((i + 1) >= argc)
			{
				error = ERROR1; //si es el ultimo caracter obviamente no tiene valor
				i++;
			}
			
			else
			{
				posible = p(&(argv[i][1]), argv[i + 1], userData);
				if (posible >= 0) {
					i += 2; //avanzo 2 parametros
					result += posible;
				}
				else {
					error = ERROR3;
					i = argc;
				}
			}
		}
		else {
			posible = p(NULL, argv[i], userData); //si no es opcion es parametro
			if (posible >= 0) {
				i++;
				result += posible;
			}
			else {
				error = ERROR3;
				i = argc;
			}
		}
	}
	if (error == ERROR1)
		final = ERROR1;
	else if (error == ERROR2)// reconoce el error
		final = ERROR2;
	else if (error == ERROR3)
		final = ERROR3;
	else
		final = result;
	return final;

}
