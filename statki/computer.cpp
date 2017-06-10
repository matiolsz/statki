#include "board.h"
#include "computer.h"

void zatopiony(Computer *komp)  //restart ustawien dla nowego statku
{
    komp->czyszukastatku=true;
    usun(komp->ostatnistatek);
    komp->drugawspolrzedna=-1;
    komp->dlugoscstatku=0;
    komp->czykoniec=false;
    komp->czyszukaustawienia=false;
    komp->pierwszyx=-1;
    komp->pierwszyy=-1;
    komp->prawa=false;
    komp->lewy=false;
    komp->dol=false;
    komp->gora=false;

    return;
}


void strzalkompa(Board *human, Computer *komp)
{
    if(komp->czyszukastatku == true)                //szuka statku na oœlep
    {
        int x=losowaliczba(human->szerokosc);       //limity
        int y=losowaliczba(human->wysokosc);
        cout << "Losowe wspolrzedne do strzalu x = " << x << " y = " << y << endl;
        if(strzal(human,x,y)==true)                 //gdy trafi
        {
            cout << "trafienie" << endl;
            komp->czyszukastatku=false;
            komp->czyszukaustawienia=true;
            komp->pierwszyx=x;
            komp->pierwszyy=y;
            return;
        }
        else
        {
            cout << "pudlo" << endl;
            return;
        }
    }

    if(komp->czyszukaustawienia==true)      //gdy szukamy ustawienia
    {

        if((komp->prawa==false)&&(komp->pierwszyx)+1<=human->szerokosc-1)
        {
            if(strzal(human,(komp->pierwszyx)+1, komp->pierwszyy)==true)
            {
                cout << "trafienie po prawej" << endl;
                komp->pozycjaostatniegostatku=POZIOMY;
                komp->drugawspolrzedna=komp->pierwszyy;
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyx);
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyx+1);
                komp->czyszukaustawienia=false;
            }
            else
            {
                cout << "po prawej pusto" << endl;
                komp->prawa = true;
            }
        }
        else if(komp->lewy==false&&komp->pierwszyx>0)
        {
            if(strzal(human,(komp->pierwszyx)-1, komp->pierwszyy)==true)
            {
                cout << "trafienie po lewej" << endl;
                komp->pozycjaostatniegostatku=POZIOMY;
                komp->drugawspolrzedna=komp->pierwszyy;
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyx-1);
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyx);
                komp->czyszukaustawienia=false;
            }
            else
            {
                cout << "po lewej pusto" << endl;
                komp->lewy = true;
            }
        }
        else if(komp->gora==false&&komp->pierwszyy>0)
        {
            if(strzal(human,komp->pierwszyx, komp->pierwszyy-1)==true)
            {
                cout << "trafienie na gorze" << endl;
                komp->pozycjaostatniegostatku=PIONOWY;
                komp->drugawspolrzedna=komp->pierwszyx;
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyy-1);
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyy);
                komp->czyszukaustawienia=false;
            }
            else
            {
                cout << "na gorze pusto" << endl;
                komp->gora = true;
            }
        }
        else if(komp->dol==false&&komp->pierwszyy+1<=human->wysokosc-1)
        {
            if(strzal(human,komp->pierwszyx, komp->pierwszyy+1)==true)
            {
                cout << "trafienie na dole" << endl;
                komp->pozycjaostatniegostatku=PIONOWY;
                komp->drugawspolrzedna=komp->pierwszyx;
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyy);
                dodaj_koniec(komp->ostatnistatek,komp->pierwszyy+1);
                komp->czyszukaustawienia=false;
            }
            else
            {
                cout << "na gorze pusto. zatopiony" << endl;
                zatopiony(komp);
                return;
            }
        }
        komp->dlugoscstatku=1; // tak naprawde to dwa
        return;
    }   //znalezlismy ustawienie, teraz strzelamy w kolejne pola

    if(komp->pozycjaostatniegostatku==PIONOWY)
    {
        if(komp->czykoniec==false&&elem_at(komp->ostatnistatek,komp->dlugoscstatku)<human->wysokosc-1)  //gdy strzelamy w dol ostatni element statku
            //(polozony najnizej nie moze byc nizej niz wysokosc tablicy
        {
            //nie osi¹gneliœmy dolnego koñca statku i strzelamy w dó³
            if( strzal(human,komp->drugawspolrzedna,elem_at(komp->ostatnistatek,komp->dlugoscstatku)+1)==true)
            {
                cout << "strzelamy w dol, trafienie" << endl;
                wydrukuj(human);
                dodaj_koniec(komp->ostatnistatek, elem_at(komp->ostatnistatek,komp->dlugoscstatku)+1);
                komp->dlugoscstatku++;
            }
            else
            {
                cout << "strzelalismy w dol i pudlo, doszlismy do konca" << endl;
                komp->czykoniec=true;
            }
        }
        else if (elem_at(komp->ostatnistatek,0)-1>=0)  //najwyzsza wsp statku nie moze byc mniejsza lub rowna 0
        {
            //dolny koniec statku zosta³ osi¹gniêty, strzelamy w górê a¿ do zniszczenia statku
            if( strzal(human,komp->drugawspolrzedna,elem_at(komp->ostatnistatek,0)-1)==true)
            {
                cout << "strzelamy w gore, trafienie" << endl;
                wydrukuj(human);
                dodaj_poczatek(&(komp->ostatnistatek),elem_at(komp->ostatnistatek,0)-1);
                komp->dlugoscstatku++;
            }
            else
            {
                cout << "uciekam stad, statek zniszczony" << endl;
                zatopiony(komp);
                wydrukuj(human);
            }
        }
        else if(elem_at(komp->ostatnistatek,0)==0)
        {
            zatopiony(komp);
            cout<<"statek popsuty"<<endl;
        }
    }
    else
    {
        if(komp->czykoniec==false&&elem_at(komp->ostatnistatek,komp->dlugoscstatku)+ 1<human->szerokosc-1)
        {
            //nie osi¹gneliœmy jeszcze prawego koñca statku i strzelamy w prawo
            if(strzal(human,elem_at(komp->ostatnistatek,komp->dlugoscstatku)+1,komp->drugawspolrzedna)==true)
            {
                //trafiliœmy, zwiêkszamy d³ugoœæ statku i nastêpnym razem strzelamy dalej
                cout << "strzelamy w prawo, trafienie" << endl;
                wydrukuj(human);
                dodaj_koniec(komp->ostatnistatek,elem_at(komp->ostatnistatek,komp->dlugoscstatku)+1);
                komp->dlugoscstatku++;
            }
            else
            {
                //pud³o, koniec statku
                cout << "koniec statku lala" << endl;
                komp->czykoniec=true;
            }
        }
        else if (elem_at(komp->ostatnistatek,0)-1>=0)
        {
            //prawy koniec statku zosta³ osi¹gniêty, strzelamy w lewo a¿ do zniszczenia statku
            if(strzal(human,elem_at(komp->ostatnistatek,0)-1,komp->drugawspolrzedna)==true)
            {
                cout << "strzelamy w lewo, trafienie" << endl;
                wydrukuj(human);
                dodaj_poczatek(&(komp->ostatnistatek),elem_at(komp->ostatnistatek,0)-1);
                komp->dlugoscstatku++;
            }
            else
            {
                cout << "koniec statku" << endl;
                zatopiony(komp);
                wydrukuj(human);
            }
        }
        else if (elem_at(komp->ostatnistatek,0)==0)
        {
            zatopiony(komp);
            cout << "statek zniszczonyy";
        }
    }
    return;
}
void stworz_kompa(Computer *komp)
{
    komp->ostatnistatek=new lista;
    //komp->ostatnistatek = new vector<int>;
    zatopiony(komp);
    return;
}
