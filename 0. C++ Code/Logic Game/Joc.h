// Joc.h
#ifndef JOC_H
#define JOC_H

#include "Tauler.h"
#include "Figura.h"
#include "vector"
#include <string>

enum Direccio {
    ESQUERRA,
    DRETA
};


class Joc {
public:
    Joc();
    ~Joc();
    /*void inicialitza(const std::string& nomFitxer);*/
    bool giraFigura(DireccioGir direccio);
    bool mouFigura(int dirX);
    int baixaFigura();
    void escriuTauler(const std::string& nomFitxer);
    void inicialitza(const string& nomFitxer);
    short colocaFigura();

    // Getters para la figura y su posición
    const Figura& getFiguraActual() const { return *m_figuraActual; }
    void setFiguraActual(Figura* figura) { m_figuraActual = figura; }
    int getPosX() const { return m_posX; }
    int getPosY() const { return m_posY; }
    bool getLlegoFinal() const { return llegoFinal; }
    void setLlegoFinal(bool llegoFinal) { this->llegoFinal = llegoFinal; }
    void actualizarFiguraActual();
    void pintarDatos(const int& MIDA);
    void quitarFiguraDeTauler();
    void novaFigura(InfoFigura figura);
    short verificarEliminarFila();
    bool getActualizarFiguras() const { return actualizarFiguras; }
    bool isGameOver();
    void pintarFiguraQueViene();

private:
    Tauler m_tauler;
    Figura* m_figuraActual;
    Figura* m_figuraSiguiente;
    int m_posX;
    int m_posY;
    int girat = 0;
    bool llegoFinal;
    bool actualizarFiguras;
};

#endif
