#ifndef FIGURA_H
#define FIGURA_H

#include "Figura.h"  // Incluye el archivo donde se define TipusFigura
#include "InfoJoc.h"  // Incluye el archivo donde se define ColorFigura
#include "GraphicManager.h"

enum DireccioGir {
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
};

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

class Figura {
public:

    Figura(TipusFigura tipo, ColorFigura color, IMAGE_NAME imageName);

    void inicialitza(TipusFigura tipus, int fila, int columna);
    
    bool mouFigura(int dirX);
    bool baixaFigura() { m_posY++; return true; } 
    void gira(DireccioGir direccio);
    int getAmplada() const;
    int getAltura() const;
    IMAGE_NAME getImageName() const;
    ColorFigura getForma(int i, int j) const;
    void setForma(int i, int j, ColorFigura color);

    short getColorRandom() const { return color_random; }
    ColorFigura getColor() const { return m_color; }
    void initializeFigura();
    void limpiar();
private:
    IMAGE_NAME m_imageName;
    TipusFigura m_tipo;
    ColorFigura m_color;
    int m_forma[MAX_ALCADA][MAX_AMPLADA];
    int m_amplada;
    int m_altura;
    int m_posCol;
    short color_random;
    int m_posY;
};

#endif  
