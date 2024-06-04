/*Guarda tota la informació necessària per gestionar una partida i la llista de puntuacions històriques.
▪ Un objecte de la classe Partida per poder gestionar el funcionament de la partida.
▪ La llista de puntuacions històriques.
▪ Aquesta llista s’ha de llegir d’un fitxer al principi del programa, s’ha d’anar actualitzant a mesura que
es van jugant partides i s’ha de tornar a guardar al fitxer quan s’acaba el programa.
▪ S’ha de guardar utilitzant alguna classe de la llibreria estàndard : forward_list o list.
▪ Els valors en aquesta llista han d’estar sempre en ordre descendent de puntuació.
▪ Altres atributs que cregueu que puguin ser necessaris per gestionar el menú del joc, la partida i les
puntuacions.
▪ Us suggerim que tingui com a mínim aquests mètodes :
▪ juga : s’encarrega d’inicialitzar i executar una partida, cridant als mètodes que calgui de la classe Partida, i
seguint el que us expliquem a la introducció a la llibreria gràfica.
▪ mostraPuntuacions : s’encarrega de mostrar per pantalla la llista de puntuacions històriques*/

#ifndef TETRIS_H
#define TETRIS_H

#include "Partida.h"
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;


typedef struct
{
    string nom;
    int punts;
} Puntuacio;


class Tetris {
public:
    Tetris(const string& fitxerPuntuacions);
    ~Tetris();

    int juga(Screen* pantalla, ModeJoc mode, const string& nomFitxerInicial, const string& nomFitxerFigures, const string& nomFitxerMoviments);
    void actualitzaPuntuacio(const string& nom, int punts);
    void mostraPuntuacions();
    void guardaPuntuacions(const string& nomFitxer);

private:
    Partida m_partida;
    list<Puntuacio> m_puntuacions;
    string m_fitxerPuntuacions;

    void ordenarPuntuacions();
};

#endif 
