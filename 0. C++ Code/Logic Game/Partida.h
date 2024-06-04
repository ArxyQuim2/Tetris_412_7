// Partida.h
#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "LlistaFigura.h"
#include "LlistaMoviment.h"
#include "Joc.h"
#include "Konami.h"

const int PUNTS_FIGURA = 10;
const int PUNTS_FILA = 100;
const int DOBLE_FILA = 150;
const int TRIPLE_FILA = 175;
const int QUADRUPLE_FILA = 200;

const int CANVI_NIVELL = 200;
const double VELOCITAT_INICIAL = 1.0;
const double CANVI_VELOCITAT = 0.8;

enum ModeJoc {
    MODE_TEST,
    MODE_NORMAL
};

using namespace std;

class Partida
{
public:
    Partida(ModeJoc mode);
    ~Partida();
    void actualitzaPunts(int nFilesEliminades);
    bool actualitza(double deltaTime);
    void inicialitza(const string& nomFitxer, const string& nomFitxerFigures, const string& nomFitxerMoviments);

    void inicialitzaFigures(const string& nomFitxer);

    void inicialitzaMoviments(const string& nomFitxer);

    bool actualitzaTest(float deltaTime);

    // Getters inline
    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }

    // Setters inline
    void setFila(int fila) { m_fila = fila; }
    void setColumna(int columna) { m_columna = columna; }

    bool getPausado() { return pausado; }
    int getPuntuacio() {
        return puntuacio;
    }

    bool getHell() { return hell; } 
 
private:
    double m_temps;
    ModeJoc m_mode;
    static const int MIDA = 4;
    int m_fila, m_columna;
    bool hell;
    int puntuacio;
    Joc joc;
    float limite_para_actualizar;
    int hileras_cumplidas;
    bool no_permitido_movimiento;
    bool limite_para_actualizar_actualizado;
    bool pausado;
    short nivell;
    LlistaFigura m_figures;
    LlistaMoviment m_moviments;
    Konami* konami;
};

#endif
