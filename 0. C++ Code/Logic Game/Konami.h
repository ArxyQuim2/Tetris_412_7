#pragma once
#include "GraphicManager.h"
#include "conio.h"

class Konami
{
public:
	Konami();
	~Konami();
	bool validar();

private:
	short iActual;
	char code[10] = { 'u', 'u', 'd', 'd', 'l', 'r', 'l', 'r', 'b', 'a' };

};


