#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;

struct Board
{
    char **plansza;
    int szerokosc,wysokosc;
    vector <int>okrety;
    int pozostalepola;
};

enum pozycjastatku
{
    PIONOWY,
    POZIOMY
};

const char WODA = '0'; //ASCII Character Code
const char TRAFIONY = 'X';
const char STATEK = '1';
const char PUDLO = 'P';

int losowaliczba(int limit);
pozycjastatku losowapozycja();
bool strzal(Board*, int, int);
void wydrukuj(Board *user);
void wydrukujkomp(Board *user);
bool sprawdz(Board *user, int n, int m, int x, pozycjastatku pionczypoz);
void czyszczenie(Board *user);
void wstawstatek(Board *user, int n, int m,int x, pozycjastatku pionczypoz);
bool losowe_statki(Board *user);
bool stworz_uzytkownikow(string nazwa_pliku, Board *player, Board *komp);
void zapisdopliku(string nazwapliku, Board *player, Board *komp );



#endif // BOARD_H_INCLUDED
