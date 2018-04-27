#pragma once
#include <stdlib.h>
#include <stdio.h>
typedef int(*pCallback) (char *, char*, void *);
int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);
enum{ERROR1=-3,ERROR2,ERROR3};
//error 1 es opcion sin valor, error 2 es opcion sin clave error3 es no encontrado


