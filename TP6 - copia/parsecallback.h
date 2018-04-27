#pragma once
#include <string>
#include <iostream>




int parseCallback(char *key, char *value, void *userData);


class userData
{
	public:
	std::string ip;
	bool iniciar;
	bool invalidData;	//un control si se ingreso mal un dato se puede borrar
	userData() { ip = "0.0.0.0"; iniciar = false; invalidData = false; };
};