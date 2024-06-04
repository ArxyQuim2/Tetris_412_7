//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"
#include "Tetris.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib") 


void mostraOpcions()
{
    cout << "MENU PRINCIPAL" << endl;
    cout << "==============" << endl;
    cout << "1. Joc en mode normal" << endl;
    cout << "2. Joc en mode test" << endl;
    cout << "3. Mostrar puntuacions" << endl;
    cout << "4. Sortir" << endl;
}

void llegeixNomFitxers(string& nomInicial, string& nomFigures, string& nomMoviments)
{
    cout << "Nom del fitxer amb l'estat inicial del tauler: ";
    getline(cin >> ws, nomInicial);

    nomInicial = "./data/Games/" + nomInicial;

    cout << "Nom del fitxer amb la sequencia de figures: ";
    getline(cin >> ws, nomFigures);
    nomFigures = "./data/Games/" + nomFigures;

    cout << "Nom del fitxer amb la sequencia de moviments: ";
    getline(cin >> ws, nomMoviments);
    nomMoviments = "./data/Games/" + nomMoviments;
}


short escogetOpcionAAccion(Tetris* tetris, Screen* pantalla) {
    short opcion;
    cout << "Escoge una opcion: ";
    cin >> opcion;
    string nomInicial, nomFigures, nomMoviments, nomJugador;
    int punts = 0;

    switch (opcion)
    {
    case 1:
        pantalla->show();
        PlaySound(TEXT("./data/Sounds/music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        punts = tetris->juga(pantalla, MODE_NORMAL, "", "", "");
        PlaySound(0, 0, 0);
        cout << "Nom del jugador: ";
        cin >> nomJugador;
        tetris->actualitzaPuntuacio(nomJugador, punts);
        break;

    case 2:
        llegeixNomFitxers(nomInicial, nomFigures, nomMoviments);
        pantalla->show();
        tetris->juga(pantalla, MODE_TEST, nomInicial, nomFigures, nomMoviments);
        break;
    case 3:
        tetris->mostraPuntuacions();
        break;
    case 4:
        tetris->guardaPuntuacions("./data/Games/puntuacions.txt");
        //Instruccio necesaria per alliberar els recursos de la llibreria 
        SDL_Quit();
        exit(0);
    default:
        cout << "OPCIO INCORRECTA" << endl;
        break;
    }

    system("pause");
}



int main(int argc, const char* argv[])
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    srand(time(nullptr));


    Screen* pantalla = new Screen(SCREEN_SIZE_X, SCREEN_SIZE_Y);

    Tetris* tetris = new Tetris("./data/Games/puntuacions.txt");
   
    while (1) {
        system("cls");
        mostraOpcions();
        escogetOpcionAAccion(tetris, pantalla);
    }

    tetris->guardaPuntuacions("./data/Games/puntuacions.txt");

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();

    return 0;
}

