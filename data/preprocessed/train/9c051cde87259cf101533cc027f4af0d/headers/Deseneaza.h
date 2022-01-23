#pragma once
#include "Coordonate.h"
#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

class Deseneaza
{

public:
	Deseneaza();
	virtual ~Deseneaza();
	virtual void Draw(coordonate&)=0;
};

