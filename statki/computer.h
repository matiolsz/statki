#ifndef COMPUTER_H_INCLUDED
#define COMPUTER_H_INCLUDED

#include "board.h"
#include "lista.h"

struct Computer
{
    bool czyszukastatku;

    struct lista *ostatnistatek;
    int drugawspolrzedna;
    pozycjastatku pozycjaostatniegostatku;
    int dlugoscstatku;

    bool czykoniec;

    bool czyszukaustawienia;
    int pierwszyx;
    int pierwszyy;
    bool prawa,dol,gora,lewy;
    //prawa dol itd oznaczaj¹, czy przy szukaniu uk³adu statku
    //strzelaliœmy ju¿ w pola po prawej, na dole itd od pierwszego trafienia

};

void zatopiony(Computer *komp) ; //restart ustawien dla nowego statku
void strzalkompa(Board *human, Computer *komp);
void stworz_kompa(Computer *komp);


#endif // COMPUTER_H_INCLUDED
