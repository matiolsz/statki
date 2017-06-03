#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

const char WODA = '0'; //ASCII Character Code
const char TRAFIONY = 'X';
const char STATEK = '1';
const char PUDLO = 'P';

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

struct Computer
{
    bool czyszukastatku;

    vector <int>ostatnistatek;
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

int losowaliczba(int limit)
{
    int x= rand()%(limit);
    return x;
}

pozycjastatku losowapozycja()
{
    int x=rand()%2;
    if(x==1)
    {
        return POZIOMY;
    }
    return PIONOWY;

}


bool strzal(Board *user, int x, int y)
{
    if(user->plansza[y][x]==WODA)
    {
        user->plansza[y][x]=PUDLO;
        return false;
    }
    else if(user->plansza[y][x]==STATEK)
    {
        user->plansza[y][x]=TRAFIONY;
        user->pozostalepola--;
        return true;
    }
    else if(user->plansza[y][x]==PUDLO)
    {
        return false;
    }
    else if(user->plansza[y][x]==TRAFIONY)
    {
        return false;
    }
    else return false;

}
void zatopiony(Computer *komp)  //restart ustawien dla nowego statku
{
    komp->czyszukastatku=true;
    komp->ostatnistatek.clear();
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

void wydrukuj(Board *user)
{
    for(int i =0; i<user->wysokosc; i++)
    {
        for(int j=0; j<user->szerokosc; j++)
        {
            cout<<user->plansza[i][j] << '\t';
        }
        cout<<endl;
    }

}
void wydrukujkomp(Board *user)
{
    for(int i =0; i<user->wysokosc; i++)
    {
        for(int j=0; j<user->szerokosc; j++)
        {
            if(user->plansza[i][j]==STATEK)
            {
                cout<<WODA<<'\t';
            }
            else
                cout<<user->plansza[i][j] << '\t';
        }
        cout<<endl;
    }

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
                komp->ostatnistatek.push_back(komp->pierwszyx);
                komp->ostatnistatek.push_back(komp->pierwszyx+1);
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
                komp->ostatnistatek.push_back(komp->pierwszyx-1);
                komp->ostatnistatek.push_back(komp->pierwszyx);
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
                komp->ostatnistatek.push_back(komp->pierwszyy-1);
                komp->ostatnistatek.push_back(komp->pierwszyy);
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
                komp->ostatnistatek.push_back(komp->pierwszyy);
                komp->ostatnistatek.push_back(komp->pierwszyy+1);
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
        if(komp->czykoniec==false&&komp->ostatnistatek.at(komp->dlugoscstatku)<human->wysokosc-1)  //gdy strzelamy w dol ostatni element statku
            //(polozony najnizej nie moze byc nizej niz wysokosc tablicy
        {
            //nie osi¹gneliœmy dolnego koñca statku i strzelamy w dó³
            if( strzal(human,komp->drugawspolrzedna,komp->ostatnistatek.at(komp->dlugoscstatku)+1)==true)
            {
                cout << "strzelamy w dol, trafienie" << endl;
                wydrukuj(human);
                komp->ostatnistatek.push_back(komp->ostatnistatek.at(komp->dlugoscstatku)+1);
                komp->dlugoscstatku++;
            }
            else
            {
                cout << "strzelalismy w dol i pudlo, doszlismy do konca" << endl;
                komp->czykoniec=true;
            }
        }
        else if (komp->ostatnistatek.at(0)-1>=0)  //najwyzsza wsp statku nie moze byc mniejsza lub rowna 0
        {
            //dolny koniec statku zosta³ osi¹gniêty, strzelamy w górê a¿ do zniszczenia statku
            if( strzal(human,komp->drugawspolrzedna,(komp->ostatnistatek.at(0))-1)==true)
            {
                cout << "strzelamy w gore, trafienie" << endl;
                wydrukuj(human);
                komp->ostatnistatek.insert(komp->ostatnistatek.begin(),komp->ostatnistatek.at(0)-1 );
                komp->dlugoscstatku++;
            }
            else
            {
                cout << "uciekam stad, statek zniszczony" << endl;
                zatopiony(komp);
                wydrukuj(human);
            }
        }
        else if(komp->ostatnistatek.at(0)==0)
        {
            zatopiony(komp);
            cout<<"statek popsuty"<<endl;
        }
    }
    else
    {
        if(komp->czykoniec==false&&komp->ostatnistatek.at(komp->dlugoscstatku) + 1<human->szerokosc-1)
        {
            //nie osi¹gneliœmy jeszcze prawego koñca statku i strzelamy w prawo
            if(strzal(human,komp->ostatnistatek.at(komp->dlugoscstatku)+1,komp->drugawspolrzedna)==true)
            {
                //trafiliœmy, zwiêkszamy d³ugoœæ statku i nastêpnym razem strzelamy dalej
                cout << "strzelamy w prawo, trafienie" << endl;
                wydrukuj(human);
                komp->ostatnistatek.push_back(komp->ostatnistatek.at(komp->dlugoscstatku)+1);
                komp->dlugoscstatku++;
            }
            else
            {
                //pud³o, koniec statku
                cout << "koniec statku lala" << endl;
                komp->czykoniec=true;
            }
        }
        else if (komp->ostatnistatek.at(0)-1>=0)
        {
            //prawy koniec statku zosta³ osi¹gniêty, strzelamy w lewo a¿ do zniszczenia statku
            if(strzal(human,komp->ostatnistatek.at(0)-1,komp->drugawspolrzedna)==true)
            {
                cout << "strzelamy w lewo, trafienie" << endl;
                wydrukuj(human);
                komp->ostatnistatek.insert(komp->ostatnistatek.begin(),komp->ostatnistatek.at(0)-1);
                komp->dlugoscstatku++;
            }
            else
            {
                cout << "koniec statku" << endl;
                zatopiony(komp);
                wydrukuj(human);
            }
        }
        else if (komp->ostatnistatek.at(0)==0)
        {
            zatopiony(komp);
            cout << "statek zniszczonyy";
        }
    }
    return;
}

void stworz_kompa(Computer *komp)
{
    //komp->ostatnistatek = new vector<int>;
    zatopiony(komp);
    return;
}


bool sprawdz(Board *user, int n, int m, int x, pozycjastatku pionczypoz)
{
    if(pionczypoz == PIONOWY)
    {
        if(m+x-1>=user->wysokosc)
        {
            return true;
        }
        for (int i=m-1; i<=m+x; i++)
        {

            if(i < 0 || i >= user->wysokosc)
            {
                continue;
            }
            for(int j=n-1; j<=n+1; j++)
            {
                if(j< 0 || j >= user->szerokosc)
                {
                    continue;
                }
                if(user->plansza[i][j]=='1')
                {
                    return true;
                }
            }
        }
    }
    else
    {
        if(n+x-1>=user->szerokosc)
        {
            return true;
        }
        for(int i=m-1; i<=m+1; i++)
        {
            if(i<0 || i>= user->wysokosc)
            {
                continue;
            }
            for(int j=n-1; j<=n+x; j++)
            {
                if(j<0||j>=user->szerokosc)
                {
                    continue;
                }
                if(user->plansza[i][j] == '1')
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void czyszczenie(Board *user)
{
    for(int i =0; i<user->szerokosc; i++)
    {
        for(int j =0; j<user->wysokosc; j++)
        {
            user->plansza[i][j]='0';
        }
    }
    return ;
}

void wstawstatek(Board *user, int n, int m,int x, pozycjastatku pionczypoz)
{
    if(pionczypoz==POZIOMY)
    {
        for(int i =n; i<=n+x-1; i++)
        {
            user->plansza[m][i]='1';
        }
    }
    else
    {
        for(int i =m; i<=m+x-1; i++)
        {
            user->plansza[i][n]='1';
        }
    }

}

bool losowe_statki(Board *user)
{
    string n;
    //int ilosc_rodzajow=user->okrety.size()/2;
    for(int i = 0; i<=user->okrety.size()-2; i+=2)
    {
        for(int j=0; j<user->okrety.at(i+1); j++)
        {

            int proby = 0;
            bool udalosie = false;

            do
            {
                int x=losowaliczba(user->szerokosc);
                int y=losowaliczba(user->wysokosc);
                pozycjastatku z=losowapozycja();

                if (sprawdz(user, x, y, user->okrety.at(i), z) == false)
                {
                    wstawstatek(user, x, y, user->okrety.at(i), z);
                    udalosie = true;
                }
                else
                {
                    proby++;
                    if(proby == 100)
                    {
                        czyszczenie(user);
                        return false;
                    }
                }
            }
            while (udalosie == false);
        }
    }
    return true;
}

bool stworz_uzytkownikow(string nazwa_pliku, Board *player, Board *komp)
{
    string tryb;
    ifstream plik(nazwa_pliku.c_str());
    if(!plik.is_open())
    {
        cerr<<"blad otwarcia pliku"<<endl;
        return false;
    }

    plik>>tryb;
    if(tryb=="NEWGAME")
    {
        bool playerstatki=false,enemystatki=false;
        plik>>player->szerokosc;
        plik>>player->wysokosc;
        komp->szerokosc=player->szerokosc;
        komp->wysokosc=player->wysokosc;

        char **x=new char *[player->wysokosc];
        char **y=new char *[komp->wysokosc];

        for(int i=0; i<player->wysokosc; i++)
        {
            x[i]=new char [player->szerokosc];
            y[i]=new char [komp->szerokosc];
        }

        for(int i=0; i<player->wysokosc; i++)
        {
            for(int j=0; j <player->szerokosc; j++)
            {
                x[i][j] = '0';
                y[i][j] = '0';
            }
        }

        player->plansza = x;
        komp->plansza = y;

        int a;
        while(!plik.eof())
        {
            plik>>a;
            player->okrety.push_back(a);
        }

        player->pozostalepola=0;


        for(int i =0; i<player->okrety.size(); i+=2)
        {
            player->pozostalepola+=player->okrety.at(i)*player->okrety.at(i+1);
        }
        cout << "liczba pozostalych pol zajetych przez statki: " << player->pozostalepola<<endl;

        komp->okrety=player->okrety;
        komp->pozostalepola=player->pozostalepola;

        for(int i=0; i<100; i++)
        {

            if (playerstatki==false)
            {
                if(losowe_statki(player)==true)
                {
                    playerstatki=true;
                }
            }
            if (enemystatki==false)
            {
                if(losowe_statki(komp)==true)
                {
                    enemystatki=true;
                }
            }

            if(playerstatki==true && enemystatki==true)
            {
                break;
            }
        }

    }
    else if(tryb=="SAVEDGAME")
    {
        cout << "test wczytywania";
        player->pozostalepola=0;
        komp->pozostalepola=0;
        plik>>player->szerokosc;
        plik>>player->wysokosc;
        komp->wysokosc=player->wysokosc;
        komp->szerokosc=player->szerokosc;

        cout << "wymiary " << player->szerokosc << " x " << player->wysokosc << endl;

        char **x=new char *[player->wysokosc];
        char **y=new char *[komp->wysokosc];

        for(int i=0; i<player->wysokosc; i++)
        {
            x[i]=new char [player->szerokosc];
            y[i]=new char [komp->szerokosc];
        }
        for(int i=0; i<player->wysokosc; i++)
        {
            for(int j =0; j<player->szerokosc; j++)
            {
                plik>>x[i][j];
                if(x[i][j]==STATEK)
                {
                    player->pozostalepola++;
                }
            }
        }
        for(int i=0; i<komp->wysokosc; i++)
        {
            for(int j =0; j<komp->szerokosc; j++)
            {
                plik>>y[i][j];
                if(y[i][j]==STATEK)
                {
                    komp->pozostalepola++;
                }
            }
        }

        player->plansza = x;
        komp->plansza = y;

    }
    return true;
}

void zapisdopliku(string nazwapliku, Board *player, Board *komp )
{
    ofstream plik(nazwapliku.c_str());
    if(!plik.is_open())
    {
        cerr<<"blad otwarcia pliku"<<endl;
        return ;
    }
    plik<<"SAVEDGAME"<<endl;
    plik<<player->szerokosc<<" "<<player->wysokosc<<endl;
    for(int i=0; i<player->wysokosc; i++)
    {
        for(int j =0; j<player->szerokosc; j++)
        {
            plik<<player->plansza[i][j]<<" ";

        }
        plik<<endl;
    }

    for(int i=0; i<komp->wysokosc; i++)
    {
        for(int j =0; j<komp->szerokosc; j++)
        {
            plik<<komp->plansza[i][j]<<" ";

        }
        plik<<endl;
    }


}

int main(int argc, char **argv)
{
    Board *player = new Board;
    Board *enemy = new Board;
    Computer *pc = new Computer;
    stworz_kompa(pc);
    int x,y;
    bool czydalej;

    if(argc == 2)
    {
        if(stworz_uzytkownikow(argv[1],player,enemy)==false)
        {
            cerr<<"blad wczytywania"<<endl;
            return 1;
        }
    } else {
        cout << "nie podano pliku konfiguracyjnego." << endl;
        return 1;
    }



    while(1)
    {
        system("cls");

        cout<<"PLANSZA WROGA: "<<endl;
        wydrukujkomp(enemy);

        cout<<endl;

        cout<<"PLANSZA GRACZA: "<<endl;
        wydrukuj(player);
        cout<<endl;
        do
        {
            czydalej=true;
            string p;
            cout<<"podaj wsp x i y lub dowolny znak, aby przejsc do zapisu"<<endl;
            cin>>x>>y;

            if(cin.fail())
            {
                czydalej=false;
                cin.clear();
                cin.sync();
                cout<<"czy chcesz zapisac gre?(t/n)"<<endl;
                cin>>p;
                if(p=="t")
                {
                    zapisdopliku("statki3.txt",player,enemy);
                    cout<<"czy chcesz wyjsc z gry?(t/n)"<<endl;
                    cin>>p;
                    if(p=="t"){
                        return 0;
                    }
                }
                cin.clear();
                cin.sync();
            }

            if(x>=player->szerokosc||y>=player->wysokosc){
                cout << "takiego pola nie ma na planszy" << endl;
                czydalej = false;
            }
        }
        while(czydalej!=true);

        if(strzal(enemy,x,y)==true)
        {
            if (enemy->pozostalepola==0)
            {
                break;
            }
        }
        strzalkompa(player,pc);
        if(player->pozostalepola==0)
        {
            break;
        }

    }

    return 0;
}
