#include "Figura.h"
#include <iostream>
#include "InfoJoc.h"

using namespace std;


void Figura::gira(DireccioGir dir) {
    if (m_tipo != FIGURA_O) {
        int temp[MAX_ALCADA][MAX_AMPLADA] = { {NO_COLOR} };
        int newHeight = m_amplada;
        int newWidth = m_altura;

        if (dir == GIR_HORARI) {
            for (int i = 0; i < m_altura; ++i) {
                for (int j = 0; j < m_amplada; ++j) {
                    temp[j][newWidth - i - 1] = m_forma[i][j];
                }
            }
        }
        else if (dir == GIR_ANTI_HORARI) {
            for (int i = 0; i < m_altura; ++i) {
                for (int j = 0; j < m_amplada; ++j) {
                    temp[newHeight - j - 1][i] = m_forma[i][j];
                }
            }
        }

        m_amplada = newWidth;
        m_altura = newHeight;

        for (int i = 0; i < MAX_ALCADA; ++i) {
            for (int j = 0; j < MAX_AMPLADA; ++j) {
                m_forma[i][j] = NO_COLOR;
            }
        }
        for (int i = 0; i < newHeight; ++i) {
            for (int j = 0; j < newWidth; ++j) {
                m_forma[i][j] = temp[i][j];
            }
        }
    }
}

Figura::Figura(TipusFigura tipo, ColorFigura color, IMAGE_NAME imageName) : m_tipo(tipo), m_color(color), m_amplada(0), m_altura(0), m_posCol(0), m_posY(0)
{
    m_imageName = imageName;
    limpiar();

    initializeFigura();

}



void Figura::inicialitza(TipusFigura tipus, int fila, int columna)
{
    limpiar();

    // Ponle un color
    m_color = (ColorFigura)(rand() % 7);
   
    m_tipo = tipus;
    m_posY = fila;
    m_posCol = columna;

    initializeFigura();
}

bool Figura::mouFigura(int dirX) {
    m_posCol += dirX;
    return true;
}

IMAGE_NAME Figura::getImageName() const
{
	return m_imageName;
}

ColorFigura Figura::getForma(int i, int j) const {
    return (ColorFigura)m_forma[i][j];
}

void Figura::setForma(int i, int j, ColorFigura color)
{
    m_forma[i][j] = color;
}

void Figura::initializeFigura()
{

    switch (m_tipo) {
    case FIGURA_O:
        m_altura = 2;
        m_amplada = 2;
        m_forma[0][0] = m_color;
        m_forma[0][1] = m_color;
        m_forma[1][0] = m_color;
        m_forma[1][1] = m_color;
        break;
    case FIGURA_I:
        m_altura = 4;
        m_amplada = 4;
        m_forma[1][0] = m_color;
        m_forma[1][1] = m_color;
        m_forma[1][2] = m_color;
        m_forma[1][3] = m_color;
        break;
    case FIGURA_T:
        m_altura = 3;
        m_amplada = 3;
        m_forma[0][1] = m_color;
        m_forma[1][0] = m_color;
        m_forma[1][1] = m_color;
        m_forma[1][2] = m_color;
        break;
    case FIGURA_L:
        m_altura = 3;
        m_amplada = 3;
        m_forma[0][2] = m_color;
        m_forma[1][0] = m_color;
        m_forma[1][1] = m_color;
        m_forma[1][2] = m_color;
        break;
    case FIGURA_J:
        m_altura = 3;
        m_amplada = 3;
        m_forma[0][0] = m_color;
        m_forma[1][0] = m_color;
        m_forma[1][1] = m_color;
        m_forma[1][2] = m_color;
        break;
    case FIGURA_Z:
        m_altura = 3;
        m_amplada = 3;
        m_forma[0][0] = m_color;
        m_forma[0][1] = m_color;
        m_forma[1][1] = m_color;
        m_forma[1][2] = m_color;
        break;
    case FIGURA_S:
        m_altura = 3;
        m_amplada = 3;
        m_forma[0][1] = m_color;
        m_forma[0][2] = m_color;
        m_forma[1][0] = m_color;
        m_forma[1][1] = m_color;
        break;
    default:
        break;
    }
}

void Figura::limpiar()
{
    // limpiar la figura
    for (int i = 0; i < MAX_ALCADA; ++i) {
        for (int j = 0; j < MAX_AMPLADA; ++j) {
            m_forma[i][j] = NO_COLOR;
        }
    }
}

int Figura::getAmplada() const {
    return m_amplada;
}

int Figura::getAltura() const {
    return m_altura;
}
