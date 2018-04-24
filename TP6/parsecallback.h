#ifndef parescallback

#include "simulation_C.h"
#include <stdio.h>
#include <string.h>
#include <string>

typedef int(*pCallback) (char * key, char * value, void * userdata);

char* strlower(char str[]);

int callback(char *key, char *value, void *userData, simulation_C *sim);

#endif