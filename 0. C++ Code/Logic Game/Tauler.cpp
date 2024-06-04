#include "Tauler.h"
#include <ostream>
#include <iostream>
#include "InfoJoc.h"

using namespace std;

Tauler::Tauler() {
    this->inicializaTauler();
}

void Tauler::inicializaTauler()
{
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            m_tauler[i][j] = NO_COLOR;
        }
    }
}


void Tauler::inicialitza(ColorFigura taulerInicial[MAX_FILA - 1][MAX_COL - 1])
{
    for (int i = 0; i < MAX_FILA - 1; i++)
        m_lliures[i] = MAX_COL - 1;

    for (int i = 1; i < MAX_FILA; i++)
        for (int j = 1; j < MAX_COL; j++)
        {
            m_tauler[i][j] = taulerInicial[i - 1][j - 1];
            if (taulerInicial[i - 1][j - 1] != NO_COLOR)
                m_lliures[i - 1]--;
        }
}

void Tauler::afegeixFigura(const Figura& figura, int pos_x, int pos_y) {
    for (int i = 0; i < figura.getAltura(); i++) {
        for (int j = 0; j < figura.getAmplada(); j++) {
            if (pos_y + i >= 0 && pos_y + i < MAX_FILA
                && pos_x + j >= 0 && pos_x + j < MAX_COL) {
                if (figura.getForma(i, j) != NO_COLOR) {
                    m_tauler[pos_y + i][pos_x + j] = figura.getForma(i, j);
                }
            }
        }
    }
}

void Tauler::eliminaFila(int fila) {
    bool filaCompleta = true;
    for (int j = 1; j < MAX_COL; j++) {
        if (m_tauler[fila][j] == NO_COLOR) {
            filaCompleta = false;
            break;
        }
    }

    if (filaCompleta) {
        for (int i = fila; i > 0; i--) {
            for (int j = 0; j < MAX_COL; j++) {
                m_tauler[i][j] = m_tauler[i - 1][j];
            }
        }

        for (int j = 0; j < MAX_COL; j++) {
            m_tauler[0][j] = NO_COLOR;
        }
    }
}

bool Tauler::estaOcupat(int posX, int posY) const {
    return (m_tauler[posY][posX] != NO_COLOR);
}

ColorFigura Tauler::getColor(int posX, int posY) const {
    return m_tauler[posY][posX];
}

void Tauler::setColor(int fila, int col, ColorFigura color) {
    m_tauler[fila][col] = color;
}

bool Tauler::esFilaCompleta(int fila) const {
    for (int j = 1; j < MAX_COL; j++) {
        if (m_tauler[fila][j] == NO_COLOR) {
            return false;
        }
    }
    return true;
}

bool Tauler::eliminaFilesCompletes() {
    int filesEliminades = 0;
    
    for (int fila = MAX_FILA - 1; fila >= 0; --fila) {
        if (esFilaCompleta(fila)) {
            filesEliminades++;

            for (int i = fila; i > 0; --i) {
                for (int j = 0; j < MAX_COL; j++) {
                    m_tauler[i][j] = m_tauler[i - 1][j];
                }
            }

            for (int j = 0; j < MAX_COL; j++) {
                m_tauler[0][j] = NO_COLOR;
            }

            fila++;
        }
    }

    return filesEliminades > 0;
}

bool Tauler::comprovaPartidaFinalitzada() const {
    for (int col = 0; col < MAX_COL; ++col) {
        if (m_tauler[0][col] != NO_COLOR) {
            return true;
        }
    }
    return false;
}

void Tauler::escriuTauler(ostream& out) const {
    for (int i = 0; i < MAX_FILA; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            out << m_tauler[i][j] << " ";
        }
        out << endl;
    }
}
