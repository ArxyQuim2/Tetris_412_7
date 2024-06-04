#include "Joc.h"
#include "Figura.h"
#include "Tauler.h"
#include "InfoJoc.h"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"
#include <vector>
#include <sstream>
#include "Tauler.h"
#include "Partida.h"

using namespace std;

Joc::Joc() {
	m_posX = 5;
	m_posY = 5;
	actualizarFiguras = false;
	llegoFinal = false;

	short color_random = rand() % 7;
	short figura_random = rand() % 7 + 1;
	short image_random = color_random + 2;
	


	m_figuraActual = new Figura((TipusFigura)figura_random, (ColorFigura)color_random, (IMAGE_NAME)image_random);
	short color_random_next = rand() % 7;
	short figura_random_next = rand() % 7 + 1;
	short image_random_next = color_random_next + 2;
	m_figuraSiguiente = new Figura((TipusFigura)figura_random_next, (ColorFigura)color_random_next, (IMAGE_NAME)image_random_next);

	for (int i = 0; i < MAX_FILA; ++i) {
		for (int j = 0; j < MAX_COL; ++j) {
			m_tauler.setColor(i, j, NO_COLOR);
		}
	}

	m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);
}
Joc::~Joc()
{
	delete m_figuraSiguiente;
	delete m_figuraActual;
}

bool Joc::giraFigura(DireccioGir direccio) {

	for (int i = 0; i < m_figuraActual->getAltura(); ++i) {
		for (int j = 0; j < m_figuraActual->getAmplada(); ++j) {
			if (m_figuraActual->getForma(i, j) != NO_COLOR) {

				GraphicManager::getInstance()->drawSprite(m_figuraActual->getImageName(),
					POS_X_TAULER + (m_posX + j) * MIDA_QUADRAT,
					POS_Y_TAULER + (m_posY + i - 1) * MIDA_QUADRAT, false);
			}
		}
	}

	int anchuraActual = m_figuraActual->getAmplada();
	int alturaActual = m_figuraActual->getAltura();

	quitarFiguraDeTauler();

	m_figuraActual->gira(direccio);

	for (int i = 0; i < m_figuraActual->getAltura(); ++i) {
		for (int j = 0; j < m_figuraActual->getAmplada(); ++j) {
			if (m_figuraActual->getForma(i, j) != NO_COLOR) {
				if (m_posY + i >= MAX_FILA || m_posX + j >= MAX_COL ||
					m_posY + i < 0 || m_posX + j <= 0 ||
					m_tauler.estaOcupat(m_posX + j, m_posY + i)
					) {
					quitarFiguraDeTauler();
					m_figuraActual->gira(direccio == GIR_HORARI ? GIR_ANTI_HORARI : GIR_HORARI);
					m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);
					return false;
				}
			}
		}
	}


	m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);

	return true;
}

bool Joc::mouFigura(int dirX) {
	for (int i = 0; i < m_figuraActual->getAltura(); ++i) {
		for (int j = 0; j < m_figuraActual->getAmplada(); ++j) {
			if (m_figuraActual->getForma(i, j) != NO_COLOR) {
				m_tauler.setColor(m_posY + i, m_posX + j, NO_COLOR);
			}
		}
	}

	int newPosX = m_posX + dirX;

	bool movimientoPermitido = true;
	for (int i = 0; i < m_figuraActual->getAltura(); ++i) {
		for (int j = 0; j < m_figuraActual->getAmplada(); ++j) {
			if (m_figuraActual->getForma(i, j) != NO_COLOR) {
				int newX = newPosX + j;
				int newY = m_posY + i;

				if (newX <= 0 || newX >= MAX_COL || newY < 0 || newY >= MAX_FILA) {
					movimientoPermitido = false;
					break;
				}
				if (m_tauler.estaOcupat(newX, newY)) {
					movimientoPermitido = false;
					break;
				}

			}
		}
		if (!movimientoPermitido) {
			break;
		}
	}

	if (movimientoPermitido) {
		m_posX = newPosX;
	}

	m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);

	return movimientoPermitido;
}
int Joc::baixaFigura() {
	// Guardar una copia del tablero actual
	ColorFigura matriz[MAX_FILA][MAX_COL];

	for (int k = 0; k < MAX_FILA; ++k) {
		for (int l = 0; l < MAX_COL; ++l) {
			matriz[k][l] = m_tauler.getColor(l, k);
		}
	}

	// Eliminar la figura actual del tablero
	quitarFiguraDeTauler();

	// Intentar mover la figura hacia abajo
	bool movimientoPermitido = true;
	int newY = m_posY + 1;
	for (int i = 0; i < m_figuraActual->getAltura(); ++i) {
		for (int j = 0; j < m_figuraActual->getAmplada(); ++j) {
			if (m_figuraActual->getForma(i, j) != NO_COLOR) {
				int actualY = newY + i;
				int actualX = m_posX + j;

				// Verificar si el movimiento es posible
				if (actualY >= MAX_FILA || m_tauler.estaOcupat(actualX, actualY)) {
					movimientoPermitido = false;
					break;
				} 
			}
		}
		if (!movimientoPermitido) {
			llegoFinal = true;
			break;
		}

	}

	// Si el movimiento es permitido, actualizar la posición de la figura
	if (movimientoPermitido) {
		m_posY = newY;
	}

	// Restaurar la figura en la nueva posición o revertir si el movimiento no es permitido
	if (movimientoPermitido) {
		m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);
	}
	else {
		// Restaurar el tablero original si el movimiento no fue permitido
		for (int k = 0; k < MAX_FILA; ++k) {
			for (int l = 0; l < MAX_COL; ++l) {
				m_tauler.setColor(k, l, matriz[k][l]);
			}
		}
		// Restaurar la figura en su posición anterior
		m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);
	}

	// Devuelve si el movimiento fue exitoso o no
	return int(movimientoPermitido);
}


void Joc::escriuTauler(const std::string& nomFitxer) {
	m_tauler.eliminaFilesCompletes();
	std::ofstream fitxerSortida(nomFitxer);
	if (fitxerSortida.is_open()) {
		m_tauler.escriuTauler(fitxerSortida);
		fitxerSortida.close();
	}
}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream* fitxer = new ifstream;
	fitxer->open(nomFitxer);
	if (fitxer->is_open())
	{
		int tipus, fila, columna, gir;
		*fitxer >> tipus >> fila >> columna >> gir;
		m_posY = fila;
		m_posX = columna;
		m_figuraActual->inicialitza(TipusFigura(tipus), fila, columna);

		for (int i = 0; i < gir; i++)
			m_figuraActual->gira(GIR_HORARI);

		ColorFigura taulerInicial[MAX_FILA - 1][MAX_COL - 1];
		int color;
		for (int i = 0; i < MAX_FILA - 1; i++)
			for (int j = 0; j < MAX_COL - 1; j++)
			{
				*fitxer >> color;
				taulerInicial[i][j] = color == COLOR_NEGRE ? NO_COLOR : ColorFigura(color);
			}

		m_tauler.inicialitza(taulerInicial);
		m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);

		fitxer->close();
	}

	delete fitxer;
}

short Joc::colocaFigura()
{
	short nFiles;
	do
	{
		baixaFigura();
		nFiles = verificarEliminarFila();
	} while (!llegoFinal);
	return nFiles;
}

void Joc::actualizarFiguraActual()
{
	short color_random = rand() % 7;
	short image_random = color_random + 2;
	short figura_random = rand() % 7 + 1;

	m_figuraActual = m_figuraSiguiente;
	m_figuraSiguiente = new Figura((TipusFigura)figura_random, (ColorFigura)color_random, (IMAGE_NAME)image_random);

	m_posX = 5;
	m_posY = 1;
	llegoFinal = false;

	m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);
}

void Joc::pintarDatos(const int& MIDA)
{
	for (int i = 0; i < MAX_FILA; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (m_tauler.getColor(j, i) != NO_COLOR) {
				int color = int(m_tauler.getColor(j, i));

				GraphicManager::getInstance()->drawSprite(IMAGE_NAME(color + 2*(color < 7) + (color >= 7)), POS_X_TAULER +
					(j) * MIDA_QUADRAT,
					POS_Y_TAULER + (i - 1) * MIDA_QUADRAT,
					false);
			}
		}
	}
}

void Joc::quitarFiguraDeTauler()
{
	for (int i = 0; i < m_figuraActual->getAltura(); ++i) {
		for (int j = 0; j < m_figuraActual->getAmplada(); ++j) {
			if (m_figuraActual->getForma(i, j) != NO_COLOR) {
				m_tauler.setColor(m_posY + i, m_posX + j, NO_COLOR);
			}
		}
	}
}

void Joc::novaFigura(InfoFigura figura)
{
	m_posX = figura.columna;
	m_posY = figura.fila;
	m_figuraActual->inicialitza(figura.tipus, figura.fila, figura.columna);
	for (int i = 0; i < figura.gir; i++)
		m_figuraActual->gira(GIR_HORARI);
	m_tauler.afegeixFigura(*m_figuraActual, m_posX, m_posY);
}

short Joc::verificarEliminarFila()
{
	short veces = 0;

	for (short j = MAX_FILA - 1; j >= 0; j--) {
		if (m_tauler.esFilaCompleta(j)) {
			m_tauler.eliminaFila(++j);
			veces++;
		}
	}


	return veces;
}

bool Joc::isGameOver()
{
	if (llegoFinal) {
		if(m_posY == 1)
			return true;
	}

	return false;
}

void Joc::pintarFiguraQueViene()
{
	for (int i = 0; i < m_figuraSiguiente->getAltura(); ++i) {
		for (int j = 0; j < m_figuraSiguiente->getAmplada(); ++j) {
			if (m_figuraSiguiente->getForma(i, j) != NO_COLOR) {
				GraphicManager::getInstance()->drawSprite(m_figuraSiguiente->getImageName(),
										POS_X_TAULER + (MAX_COL + 2 + j) * MIDA_QUADRAT,
										POS_Y_TAULER + (MAX_FILA - m_figuraSiguiente->getAltura() + i - 1) * MIDA_QUADRAT, false);
			}
		}
	}
}
