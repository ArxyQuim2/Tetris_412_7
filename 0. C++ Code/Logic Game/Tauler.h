#ifndef TAULER_H
#define TAULER_H
#include <ostream>
#include "Figura.h"

const int MAX_FILA = 22;
const int MAX_COL = 12;

class Tauler {
public:
    Tauler();
    void inicializaTauler();
    void inicialitza(ColorFigura taulerInicial[MAX_FILA - 1][MAX_COL - 1]);
    bool esFilaCompleta(int fila) const;
    void afegeixFigura(const Figura& figura, int pos_x, int pos_y);
    void eliminaFila(int fila);
    bool estaOcupat(int posX, int posY) const;
    ColorFigura getColor(int posX, int posY) const;
    void setColor(int fila, int col, ColorFigura color);
    bool mouFigura(DireccioGir dir);
    bool eliminaFilesCompletes();
    bool comprovaPartidaFinalitzada() const;
    void escriuTauler(std::ostream& out) const;
private:
    ColorFigura m_tauler[MAX_FILA][MAX_COL];
    int m_lliures[MAX_FILA - 1];

};

#endif 
