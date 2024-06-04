#include "Konami.h"
#include "iostream"

Konami::Konami()
{
	iActual = 0;
}

Konami::~Konami()
{
}

bool Konami::validar()
{

	if (Keyboard_GetKeyTrg(KEYBOARD_UP) && code[iActual] == 'u' ||
		Keyboard_GetKeyTrg(KEYBOARD_DOWN) && code[iActual] == 'd' ||
		Keyboard_GetKeyTrg(KEYBOARD_LEFT) && code[iActual] == 'l' ||
		Keyboard_GetKeyTrg(KEYBOARD_RIGHT) && code[iActual] == 'r' ||
		Keyboard_GetKeyTrg(KEYBOARD_B) && code[iActual] == 'b' ||
		Keyboard_GetKeyTrg(KEYBOARD_A) && code[iActual] == 'a'
		) {
		iActual++;
	}




	return iActual >= 10;
}
