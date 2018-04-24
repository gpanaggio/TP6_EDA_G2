#pragma once
#include "simulation_C.h"
#include <stdio.h>

typedef int(*pCallback) (char *, char*, void *, simulation_C *);
int parseCmdLine(int argc, char *argv[], pCallback p, void *userData, simulation_C * sim);
