#include "Tetris.h"

/*⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ 
⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ 
⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ 
⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉
*/

Tetris::Tetris(const string& fitxerPuntuacions): m_partida(MODE_NORMAL)
{
    ifstream* fitxer = new ifstream;
    fitxer->open(fitxerPuntuacions);
    if (fitxer->is_open())
    {
        Puntuacio p;
        *fitxer >> p.nom >> p.punts;
        while (!fitxer->eof())
        {
            m_puntuacions.push_back(p);
            *fitxer >> p.nom >> p.punts;
        }
        fitxer->close();
    }
    delete fitxer;
}

Tetris::~Tetris()
{
}

int Tetris::juga(Screen* pantalla, ModeJoc mode, const string& nomFitxerInicial, const string& nomFitxerFigures, const string& nomFitxerMoviments)
{
    pantalla->show();

    Partida* game = new Partida(mode);

    game->inicialitza(nomFitxerInicial, nomFitxerFigures, nomFitxerMoviments);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    bool seguido = true;
    do
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla->processEvents();

        bool seguir = game->actualitza(deltaTime);

        if (!seguir && game->getPausado()) {
            seguido = seguir;
           continue;
        }


        // Actualitza la pantalla
        if(seguido) pantalla->update();

        seguido = seguir;

        if (pantalla->isExit()) {
            break;
        }
        
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));

    int puntuacio = game->getPuntuacio();
    delete game;
    // Sortim del bucle si pressionem ESC

    return puntuacio;
}

void Tetris::actualitzaPuntuacio(const string& nom, int punts) {
    list<Puntuacio>::iterator it = m_puntuacions.begin();
    bool trobat = false;
    while (!trobat && (it != m_puntuacions.end()))
    {
        if (it->punts > punts)
            trobat = true;
        else
            it++;
    }

    Puntuacio p;
    p.nom = nom;
    p.punts = punts;
    m_puntuacions.insert(it, p);
}

void Tetris::mostraPuntuacions()
{
    list<Puntuacio>::iterator it = m_puntuacions.begin();
    int ordre = 1;
    cout << endl;
    cout << "LLISTA DE PUNTUACIONS" << endl;
    cout << "======================" << endl;
    while (it != m_puntuacions.end())
    {
        cout << ordre << ". " << it->nom << " " << it->punts << endl;
        ordre++;
        it++;
    }
    cout << endl;
}

void Tetris::guardaPuntuacions(const string& nomFitxer)
{
    ofstream* fitxer = new ofstream;
    fitxer->open(nomFitxer);
    list<Puntuacio>::iterator it = m_puntuacions.begin();
    while (it != m_puntuacions.end())
    {
        *fitxer << it->nom << " " << it->punts << endl;
        it++;
    }
    fitxer->close();

    delete fitxer;
}
