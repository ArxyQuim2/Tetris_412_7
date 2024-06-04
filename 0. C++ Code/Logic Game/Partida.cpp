#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "Joc.h"
#include "Figura.h"
#include "iostream"
#include "fstream"

using namespace std;


Partida::Partida(ModeJoc mode) : joc()
{
	this->konami = new Konami();
	hell = false;
	m_mode = mode;
	m_temps = 0;
	puntuacio = 0;
	no_permitido_movimiento = false;
	m_fila = 1;
	m_columna = 5;
	limite_para_actualizar = 1.0;
	limite_para_actualizar_actualizado = false;
	pausado = false;
	nivell = 1;
}

Partida::~Partida()
{
	delete konami;
}

void Partida::actualitzaPunts(int nFilesEliminades)
{
	if (nFilesEliminades == 0)
		puntuacio += PUNTS_FIGURA;
	else
	{
		puntuacio += PUNTS_FILA;
		switch (nFilesEliminades)
		{
		case 2:
			puntuacio += DOBLE_FILA;
			break;
		case 3:
			puntuacio += TRIPLE_FILA;
			break;
		case 4:
			puntuacio += QUADRUPLE_FILA;
			break;
		}
	}

	if (puntuacio > 0 && puntuacio >= 2500 * nivell && !limite_para_actualizar_actualizado) {
		limite_para_actualizar *= CANVI_VELOCITAT;
		nivell++;
		limite_para_actualizar_actualizado = true;
	}
	else if (puntuacio > 0 && puntuacio < 2500 * nivell && limite_para_actualizar_actualizado) {
		limite_para_actualizar_actualizado = false;
	}

}


bool Partida::actualitza(double deltaTime)
{
	if (m_mode == MODE_TEST) return this->actualitzaTest(deltaTime);
	// Dibuixar el fons i el tauler
	GraphicManager::getInstance()->drawSprite(hell ? GRAFIC_HELL : GRAFIC_FONS, 0, 0, false);
	GraphicManager::getInstance()->drawSprite(hell ? GRAFIC_HELL_TAULER : GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

	// Interacció amb el teclat

	if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)) {
		joc.mouFigura(1);
	}
	else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT)) {
		joc.mouFigura(-1);
	}
	else if (Keyboard_GetKeyTrg(KEYBOARD_UP)) {
		// Llamada a la función gira con dirección horario
		// Assumes joc is a member or accessible object of type Joc
		joc.giraFigura(DireccioGir::GIR_HORARI);
	}
	else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN)) {
		// Llamada a la función gira con dirección antihorario
		// Assumes joc is a member or accessible object of type Joc
		joc.giraFigura(DireccioGir::GIR_ANTI_HORARI);
	}
	else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE)) {
		joc.baixaFigura();
	}
	if (Keyboard_GetKeyTrg(KEYBOARD_P)) {
		pausado = !pausado;
	}


	if (pausado) {
		return false;
	}

	// Introduir un temps d'espera
	m_temps += deltaTime;

	if (m_temps > limite_para_actualizar) {
		if (m_fila < N_FILES_TAULER - MIDA + 3) {
			joc.baixaFigura();
		}
		m_temps = 0.0;
	}

	// Dibuixar la figura en la nova posició

	joc.pintarDatos(MIDA);
	joc.pintarFiguraQueViene();


	if (joc.isGameOver()) {
		// Mostrar mensaje de Game Over
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, "GAME OVER");
		return false;
	}

	if (joc.getLlegoFinal()) {
		short nFilasEliminadas = joc.verificarEliminarFila();
		joc.actualizarFiguraActual();
		actualitzaPunts(nFilasEliminadas);
	}

	bool hell_antiguo = hell;
	hell = konami->validar();

	if (!hell_antiguo && hell) {
		limite_para_actualizar *= 0.2;
	}


	//Mostra la puntuació
	string puntuacioMsg = "Puntuacio: " + to_string(puntuacio);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 90, 1.0, puntuacioMsg);

	string nivellMsg = "Nivel: " + to_string(nivell);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + MIDA_QUADRAT * 8, POS_Y_TAULER - 90, 1.0, nivellMsg);
	// Mostrar la posició actual de la figura

	return true;
}

void Partida::inicialitza(const string& nomFitxer, const string& nomFitxerFigures, const string& nomFitxerMoviments)
{

	if (m_mode == MODE_TEST) {
		joc.inicialitza(nomFitxer);
		inicialitzaFigures(nomFitxerFigures);
		inicialitzaMoviments(nomFitxerMoviments);
	}

}

void Partida::inicialitzaFigures(const string& nomFitxer)
{
	ifstream* fitxer = new ifstream;
	fitxer->open(nomFitxer);
	if (fitxer->is_open())
	{
		InfoFigura figura;
		int tipus;
		*fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir;
		figura.tipus = TipusFigura(tipus);
		while (!fitxer->eof())
		{
			m_figures.insereix(figura);
			*fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir;
			figura.tipus = TipusFigura(tipus);
		}
		fitxer->close();
	}
	delete fitxer;
}

void Partida::inicialitzaMoviments(const string& nomFitxer)
{
	ifstream* fitxer = new ifstream;
	fitxer->open(nomFitxer);
	if (fitxer->is_open())
	{
		int tipus;
		*fitxer >> tipus;
		while (!fitxer->eof())
		{
			m_moviments.insereix(TipusMoviment(tipus));
			*fitxer >> tipus;
		}
		fitxer->close();
	}
	delete fitxer;
}

bool Partida::actualitzaTest(float deltaTime)
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

	m_temps += deltaTime;
	if (m_temps > limite_para_actualizar)
	{
		m_temps = 0.0;
		TipusMoviment moviment;
		if (m_moviments.esBuida())
		{
			return false;
		}
		else
		{
			moviment = m_moviments.getPrimer();
			m_moviments.limpiar();
			int nFilesEliminades;
			switch (moviment)
			{
			case MOVIMENT_DRETA:
				joc.mouFigura(1);
				break;
			case MOVIMENT_ESQUERRA:
				joc.mouFigura(-1);
				break;
			case MOVIMENT_GIR_HORARI:
				joc.giraFigura(GIR_HORARI);
				break;
			case MOVIMENT_GIR_ANTI_HORARI:
				joc.giraFigura(GIR_ANTI_HORARI);
				break;
			case MOVIMENT_BAIXA_FINAL:
				nFilesEliminades = joc.colocaFigura();
				actualitzaPunts(nFilesEliminades);
				if (!m_figures.esBuida())
				{
					InfoFigura figura = m_figures.getPrimer();
					m_figures.limpiar();
					joc.novaFigura(figura);
					joc.setLlegoFinal(false);
				}
				else
					return false;
				break;
			case MOVIMENT_BAIXA:
				nFilesEliminades = joc.colocaFigura();
				if (nFilesEliminades > 0)
				{
					actualitzaPunts(nFilesEliminades);
					if (!m_figures.esBuida())
					{
						InfoFigura figura = m_figures.getPrimer();
						m_figures.limpiar();
						joc.novaFigura(figura);
						joc.setLlegoFinal(false);
					}
					else
						return false;
				}
			}
		}

	}

	joc.pintarDatos(MIDA);
	joc.pintarFiguraQueViene();

	if (m_figures.esBuida()) {
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + MAX_COL / 2 - 10,
			POS_Y_TAULER - 50, 1.0, "GAME OVER");
		return false;
	}

	//Mostra la puntuació
	string puntuacioMsg = "Puntuacio: " + to_string(puntuacio);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 90, 1.0, puntuacioMsg);

	string nivellMsg = "Nivell: " + to_string(nivell);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + MIDA_QUADRAT * 9, POS_Y_TAULER - 90, 1.0, nivellMsg);
	// Mostrar la posició actual de la figura
	string msg = "Fila: " + to_string(joc.getPosY()) + ", Columna: " + to_string(joc.getPosX());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.8, msg);

}